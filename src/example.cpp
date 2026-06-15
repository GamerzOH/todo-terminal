#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <vector>
#include <string>
#include <algorithm>

using namespace ftxui;

int main() {
    auto screen = ScreenInteractive::TerminalOutput();

    // 1. Data State
    std::vector<std::string> all_words = {
        "apple", "application", "banana", "blackberry",
        "cherry", "coconut", "grape", "orange", "pear",
        "pineapple", "strawberry", "watermelon"
    };

    std::string search_query;
    std::vector<std::string> filtered_words;
    int menu_selected = 0;

    // 2. Logic to update suggestions
    auto update_suggestions = [&]() {
        filtered_words.clear();
        menu_selected = 0;

        if (search_query.empty()) return;

        for (const auto& word : all_words) {
            // Simple substring match (can be changed to prefix match)
            if (word.find(search_query) != std::string::npos) {
                filtered_words.push_back(word);
            }
        }
    };

    // 3. Configure Input
    InputOption input_option;
    input_option.on_change = update_suggestions;
    input_option.on_enter = [&]() {
        // If the user hits enter while typing, autocomplete with the top match
        if (!filtered_words.empty()) {
            search_query = filtered_words[menu_selected];
            filtered_words.clear();
        }
    };

    Component input = Input(&search_query, "Type to search...", input_option);

    // 4. Configure Menu (Dropdown)
    MenuOption menu_option;
    menu_option.on_enter = [&]() {
        // If the user hits enter on a menu item, apply it to the input
        if (!filtered_words.empty()) {
            search_query = filtered_words[menu_selected];
            filtered_words.clear();
            input->TakeFocus(); // Return cursor to the input box
        }
    };

    Component menu = Menu(&filtered_words, &menu_selected, menu_option);

    // 5. Wrap in Container and handle navigation
    auto container = Container::Vertical({input, menu});

    auto event_handler = CatchEvent(container, [&](Event event) {
        // ArrowDown: Move focus from the Input box down to the Menu
        if (event == Event::ArrowDown && input->Focused() && !filtered_words.empty()) {
            menu->TakeFocus();
            return true;
        }
        // ArrowUp: Move focus from the top of the Menu back to the Input box
        if (event == Event::ArrowUp && menu->Focused() && menu_selected == 0) {
            input->TakeFocus();
            return true;
        }
        return false;
    });

    // 6. Visual rendering
    auto renderer = Renderer(event_handler, [&] {
        Elements elements;

        // Draw the input box
        elements.push_back(hbox({
            text(" Search: ") | bold,
            input->Render()
        }) | border);

        // Draw the autocomplete dropdown only if there are suggestions
        if (!filtered_words.empty()) {
            elements.push_back(menu->Render() | border);
        }

        return vbox(elements) | size(WIDTH, LESS_THAN, 50);
    });

    screen.Loop(renderer);

    return 0;
}
