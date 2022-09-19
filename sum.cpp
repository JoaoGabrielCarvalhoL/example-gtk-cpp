#include <gtkmm.h>
#include <iostream>
#include <cstdlib>
#include <cctype> 
#include <regex>

using namespace Gtk;

Window* pWindow; 
Entry* num1, *num2, *result; 
Button* btn_sum;

bool is_number(std::string value) { 
	std::regex re("^[0-9]+$"); 
	std::smatch match; 
	return std::regex_search(value, match, re);
}

void on_btn_sum_clicked(){
	std::string x = num1->get_text();
	std::string y = num2->get_text();
	std::cout << x << " " << y << std::endl;

	if (is_number(x) && is_number(y)) {
		int first_number = std::stoi(x);
		int second_number = std::stoi(y);

		std::cout << first_number << " " << second_number << std::endl;
		result->set_text(std::to_string(first_number + second_number));
	} else {
		std::cout << "Error: Numbers must be provided!" << std::endl; 
		return;
	}
}

int main(int argc, char** argv) {
	
	auto app = Application::create(argc, argv, "org.gtkmm.example");
	auto refBuilder = Builder::create();

	refBuilder->add_from_file("sum.glade");
	refBuilder->get_widget("window", pWindow);

	if(pWindow) {
		refBuilder->get_widget("input_first", num1);
		refBuilder->get_widget("input_second", num2);
		refBuilder->get_widget("input_result", result);
		refBuilder->get_widget("btn_sum", btn_sum);
	}

	if (btn_sum) {
		btn_sum->signal_clicked().connect(sigc::ptr_fun(on_btn_sum_clicked));
	}

	app->run(*pWindow);

	delete pWindow; 
	return 0;
}

/*
g++ sum.cpp $(pkg-config gtkmm-3.0 --cflags --libs) -export-dynamic

*/
