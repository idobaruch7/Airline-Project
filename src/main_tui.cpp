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
    std::vector<std::string> tab_entries = {
        "📊 Dashboard",
        "👥 Crew Members",
        "🛬 Planes",
        "🛫 Flights",
        "💾 Save & Exit"
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


    // --- Main Layout ---
    auto tab_content = Container::Tab({
        dashboard_render,
        crew_render,
        planes_render,
        flights_render,
        Renderer([&screen]{ 
            return vbox({
                text("Are you sure you want to exit?"),
                separatorEmpty(),
            }) | center; 
        })
    }, &tab_index);

    // Add a quit button logic
    auto quit_button = Button("Quit Application", screen.ExitLoopClosure());
    
    // Combine sidebar and main content
    auto main_container = Container::Vertical({
        tab_selection,
        tab_content,
        quit_button
    });

    auto render_layout = Renderer(main_container, [&] {
        // If we selected "Save & Exit"
        if (tab_index == 4) {
            return window(text(" Exit "), vbox({
                text("Data saved automatically (simulated)."),
                separatorEmpty(),
                quit_button->Render() | center
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
    
    // Save on exit
    try {
        company->saveToFile("data/Delta.txt");
    } catch (...) {}

    return 0;
}