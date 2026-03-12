#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>

#include "CFlightCompany.h"
#include "CPlane.h"
#include "CCargo.h"
#include "CCrewMember.h"
#include "CPilot.h"
#include "CHost.h"
#include "CFlight.h"

using namespace ftxui;
using namespace std;

// Helper function to create the company data model
std::unique_ptr<CFlightCompany> loadCompanyData() {
    try {
        return std::make_unique<CFlightCompany>("data/Delta.txt", 0);
    } catch (...) {
        return std::make_unique<CFlightCompany>("Delta Airlines");
    }
}

int main() {
    auto screen = ScreenInteractive::Fullscreen();
    auto company = loadCompanyData();

    // Application state
    int tab_index = 0;
    bool should_save = false; // Flag to determine if we should save on exit

    std::vector<std::string> tab_entries = {
        "📊 Dashboard",
        "👥 Crew Members",
        "🛩 Planes",
        "🛫 Flights",
        "📝 Manage Data",
        "🚪 Exit Options"
    };

    auto tab_selection = Radiobox(&tab_entries, &tab_index);

    // --- Dashboard View ---
    auto dashboard_render = Renderer([&] {
        return vbox({
            text("🏢 " + company->getName()) | bold | center,
            separator(),
            vbox({
                text("Welcome to the Airline Management System!") | center,
                text("Use the left menu to navigate through the application.") | center | dim,
                separatorEmpty(),
                hbox({
                    window(text(" Quick Stats "), vbox({
                        text("Total Planes: " + to_string(company->getPlaneCount())), 
                        text("Total Crew: " + to_string(company->getCrewCount())),
                        text("Total Flights: " + to_string(company->getFlightCount())),
                    })) | flex,
                })
            }) | flex | center
        });
    });

    // --- Crew View ---
    auto crew_render = Renderer([&company] {
        std::vector<std::vector<std::string>> table_data = {
            {"Name", "Role", "Minutes", "Details"}
        };

        for (int i = 0; i < company->getCrewCount(); i++) {
            CCrewMember* c = company->getCrewMember(i);
            if (!c) continue;

            string role = "Unknown";
            string details = "-";
            
            if (CPilot* p = dynamic_cast<CPilot*>(c)) {
                role = "Pilot";
                details = p->getIsCaptain() ? "Captain" : "Co-Pilot";
                if (p->hasAddress()) details += " (Home: " + p->getAddress()->getCity() + ")";
            }
            else if (CHost* h = dynamic_cast<CHost*>(c)) {
                role = "Host";
                if (h->getHostType() == CHost::ePurser) details = "Purser";
                else if (h->getHostType() == CHost::eSuper) details = "Super";
                else details = "Regular";
            }

            table_data.push_back({c->getName(), role, to_string(c->getAirTime()), details});
        }

        auto table = Table(table_data);
        table.SelectAll().DecorateCells(center);
        table.SelectAll().Border(LIGHT);
        table.SelectRow(0).DecorateCells(bold);
        table.SelectRow(0).BorderBottom(LIGHT);
        
        // Custom padding buffer
        auto buffer = [](Element e) { return hbox({text(" "), std::move(e), text(" ")}); };
        table.SelectAll().DecorateCells(buffer);
        
        // Flexible wrapper for details column
        table.SelectColumn(3).DecorateCells(ftxui::size(WIDTH, LESS_THAN, 40));

        return vbox({
            text("👥 CREW DIRECTORY") | bold | center,
            separator(),
            table.Render() | center
        });
    });

    // --- Planes View ---
    auto planes_render = Renderer([&company] {
        std::vector<std::vector<std::string>> table_data = {
            {"Serial", "Model", "Seats", "Type Info"}
        };

        for (int i = 0; i < company->getPlaneCount(); i++) {
            CPlane& p = (*company)[i];
            
            string typeInfo = "Standard Plane";
            if (const CCargo* cargo = dynamic_cast<const CCargo*>(&p)) {
                typeInfo = "Cargo [" + to_string(static_cast<int>(cargo->getCurrCargoWeightKg())) + "/" 
                           + to_string(static_cast<int>(cargo->getMaxCargoWeightKg())) + " kg]";
            }

            table_data.push_back({
                to_string(p.getSerialNumber()),
                p.getModelName(),
                to_string(p.getSeatCount()),
                typeInfo
            });
        }

        auto table = Table(table_data);
        table.SelectAll().DecorateCells(center);
        table.SelectAll().Border(LIGHT);
        table.SelectRow(0).DecorateCells(bold);
        table.SelectRow(0).BorderBottom(LIGHT);

        // Custom padding buffer
        auto buffer = [](Element e) { return hbox({text(" "), std::move(e), text(" ")}); };
        table.SelectAll().DecorateCells(buffer);

        return vbox({
            text("🛬 FLEET DIRECTORY") | bold | center,
            separator(),
            table.Render() | center
        });
    });

    // --- Flights View ---
    auto flights_render = Renderer([&company] {
        std::vector<std::vector<std::string>> table_data = {
            {"Flight #", "Destination", "Duration", "Distance", "Assigned Plane", "Crew"}
        };

        for (int i = 0; i < company->getFlightCount(); i++) {
            CFlight* f = company->getFlight(i);
            if (!f) continue;
            
            const CFlightInfo& info = f->getFlightInfo();
            
            string planeInfo = "None";
            if (f->hasPlane()) {
                planeInfo = f->getPlane()->getModelName() + " (#" + to_string(f->getPlane()->getSerialNumber()) + ")";
            }

            table_data.push_back({
                to_string(info.getFlightNumber()),
                info.getDest(),
                to_string(info.getFlightTimeMinutes()) + " mins",
                to_string(info.getDistanceKM()) + " km",
                planeInfo,
                to_string(f->getCrewCount()) + " members"
            });
        }

        auto table = Table(table_data);
        table.SelectAll().DecorateCells(center);
        table.SelectAll().Border(LIGHT);
        table.SelectRow(0).DecorateCells(bold);
        table.SelectRow(0).BorderBottom(LIGHT);

        // Custom padding buffer
        auto buffer = [](Element e) { return hbox({text(" "), std::move(e), text(" ")}); };
        table.SelectAll().DecorateCells(buffer);

        return vbox({
            text("🛫 ACTIVE FLIGHTS") | bold | center,
            separator(),
            table.Render() | center
        });
    });


    // --- Manage Data View ---
    int form_type_index = 0;
    std::vector<std::string> form_types = {"Add Plane", "Add Crew Member", "Add Flight"};
    auto form_selection = Radiobox(&form_types, &form_type_index);

    // Plane form inputs
    std::string input_model = "";
    std::string input_seats = "";
    int plane_type_index = 0;
    std::vector<std::string> plane_types = {"Regular", "Cargo"};
    auto plane_type_selection = Radiobox(&plane_types, &plane_type_index);
    std::string input_weight = "";
    std::string input_volume = "";

    // Crew form inputs
    std::string input_name = "";
    std::string input_minutes = "";
    int crew_type_index = 0;
    std::vector<std::string> crew_types = {"Pilot", "Host"};
    auto crew_type_selection = Radiobox(&crew_types, &crew_type_index);
    bool is_captain = false;
    int host_type_index = 0;
    std::vector<std::string> host_types = {"Regular", "Super", "Purser"};
    auto host_type_selection = Dropdown(&host_types, &host_type_index);

    // Flight form inputs
    std::string input_dest = "";
    std::string input_flight_num = "";
    std::string input_duration = "";
    std::string input_distance = "";

    std::string form_message = "";

    // Submission Actions
    auto submit_plane = [&] {
        try {
            int seats = stoi(input_seats);
            if (plane_type_index == 0) {
                CPlane plane(seats, input_model);
                if (company->addPlane(plane)) form_message = "Success: Plane added!";
                else form_message = "Error: Could not add plane.";
            } else {
                float weight = stof(input_weight);
                float volume = stof(input_volume);
                CCargo cargo(seats, input_model, weight, volume, 0, 0);
                if (company->addPlane(cargo)) form_message = "Success: Cargo plane added!";
                else form_message = "Error: Could not add cargo plane.";
            }
            input_model = ""; input_seats = ""; input_weight = ""; input_volume = "";
        } catch (...) { form_message = "Error: Invalid numeric input."; }
    };

    auto submit_crew = [&] {
        try {
            int mins = stoi(input_minutes);
            if (crew_type_index == 0) {
                CPilot pilot(input_name, is_captain, nullptr, mins);
                if (company->addCrewMember(pilot)) form_message = "Success: Pilot added!";
                else form_message = "Error: Could not add pilot.";
            } else {
                CHost host(input_name, static_cast<CHost::eHostType>(host_type_index), mins);
                if (company->addCrewMember(host)) form_message = "Success: Host added!";
                else form_message = "Error: Could not add host.";
            }
            input_name = ""; input_minutes = "";
        } catch (...) { form_message = "Error: Invalid numeric input."; }
    };

    auto submit_flight = [&] {
        try {
            int fnum = stoi(input_flight_num);
            int mins = stoi(input_duration);
            int dist = stoi(input_distance);
            CFlightInfo info(input_dest, fnum, mins, dist);
            CFlight flight(info);
            if (company->addFlight(flight)) form_message = "Success: Flight added!";
            else form_message = "Error: Could not add flight.";
            input_dest = ""; input_flight_num = ""; input_duration = ""; input_distance = "";
        } catch (...) { form_message = "Error: Invalid numeric input."; }
    };

    // Input options for styling (placeholder is normal, text is bright/bold)
    InputOption input_opt;
    input_opt.transform = [](InputState state) {
        if (state.is_placeholder) {
            return state.element; // Normal terminal color for placeholders (e.g. "Enter Model Name")
        }
        return state.element | dim; // Dimmer color for the text being typed by the user
    };

    // Form containers
    auto plane_form = Container::Vertical({
        Input(&input_model, "Enter Model Name (e.g. Boeing-737)", input_opt),
        Input(&input_seats, "Enter Seat Count (e.g. 150)", input_opt),
        plane_type_selection,
        Maybe(Container::Vertical({
            Input(&input_weight, "Enter Max Weight kg (e.g. 5000)", input_opt),
            Input(&input_volume, "Enter Max Volume m3 (e.g. 200)", input_opt),
        }), [&] { return plane_type_index == 1; }),
        Button("Submit Plane", submit_plane, ButtonOption::Ascii())
    });

    auto crew_form = Container::Vertical({
        Input(&input_name, "Enter Name", input_opt),
        Input(&input_minutes, "Enter Flight Minutes", input_opt),
        crew_type_selection,
        Maybe(Checkbox("Is Captain?", &is_captain), [&] { return crew_type_index == 0; }),
        Maybe(host_type_selection, [&] { return crew_type_index == 1; }),
        Button("Submit Crew Member", submit_crew, ButtonOption::Ascii())
    });

    auto flight_form = Container::Vertical({
        Input(&input_dest, "Enter Destination", input_opt),
        Input(&input_flight_num, "Enter Flight Number (e.g. 303)", input_opt),
        Input(&input_duration, "Enter Duration in mins", input_opt),
        Input(&input_distance, "Enter Distance in km", input_opt),
        Button("Submit Flight", submit_flight, ButtonOption::Ascii())
    });

    auto forms_container = Container::Tab({plane_form, crew_form, flight_form}, &form_type_index);
    auto manage_data_container = Container::Vertical({form_selection, forms_container});

    auto manage_data_render = Renderer(manage_data_container, [&] {
        return vbox({
            text("📝 MANAGE DATA") | bold | center,
            separator(),
            hbox({
                window(text(" Select Entry Type "), form_selection->Render()),
                window(text(" Input Form "), forms_container->Render() | flex) | flex
            }) | flex,
            text(form_message) | center | color(Color::YellowLight)
        });
    });

    // --- Main Layout ---
    auto tab_content = Container::Tab({
        dashboard_render,
        crew_render,
        planes_render,
        flights_render,
        manage_data_render,
        Renderer([&screen]{ 
            return vbox({
                text("Are you sure you want to exit?"),
                separatorEmpty(),
            }) | center; 
        })
    }, &tab_index);

    // Add exit buttons logic
    auto save_and_quit_button = Button("Save & Quit", [&] {
        should_save = true;
        screen.ExitLoopClosure()();
    }, ButtonOption::Ascii());

    auto quit_without_saving_button = Button("Quit Without Saving", [&] {
        should_save = false;
        screen.ExitLoopClosure()();
    }, ButtonOption::Ascii());

    auto go_back_button = Button("Go Back", [&] {
        tab_index = 0; // Return to dashboard
    }, ButtonOption::Ascii());
    
    // Combine sidebar and main content
    auto main_container = Container::Vertical({
        tab_selection,
        tab_content,
        save_and_quit_button,
        quit_without_saving_button,
        go_back_button
    });

    auto render_layout = Renderer(main_container, [&] {
        // If we selected "Exit Options" (now index 5)
        if (tab_index == 5) {
            return window(text(" Exit Options "), vbox({
                text("Would you like to save your changes to Delta.txt before exiting?"),
                separatorEmpty(),
                hbox({
                    save_and_quit_button->Render() | color(Color::Green) | center | flex,
                    text("   "),
                    quit_without_saving_button->Render() | color(Color::Red) | center | flex
                }) | center,
                separatorEmpty(),
                go_back_button->Render() | center
            }) | center);
        }

        return hbox({
            vbox({
                text("NAVIGATION") | bold,
                separator(),
                tab_selection->Render(),
                filler(),
                text(" Airline v1.0 ") | dim
            }) | size(WIDTH, EQUAL, 25) | border,
            tab_content->Render() | flex | border
        });
    });

    screen.Loop(render_layout);
    
    // Save on exit based on user choice
    if (should_save) {
        try {
            company->saveToFile("data/Delta.txt");
        } catch (...) {}
    }

    return 0;
}