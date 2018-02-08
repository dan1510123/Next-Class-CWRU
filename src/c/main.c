#include <pebble.h>

static Window *s_main_window;
static TextLayer *background_layer;
static TextLayer *s_time_layer;
static TextLayer *just_words;
static TextLayer *min_left;
static char text[50];

static void update_time() {
	// Get a tm structure
	time_t temp = time(NULL); 
	struct tm *tick_time = localtime(&temp);
	text_layer_set_text(min_left, text);

	// Create a long-lived buffer
	static char buffer[] = "0000000";

	// Write the current hours and minutes into the buffer

	strftime(buffer, sizeof("0123456"), "%w|%H:%M", tick_time);

	// Display this time on the TextLayer
	text_layer_set_text(s_time_layer, buffer);

	int currh = ((buffer[2] - '0')*10 + (buffer[3] - '0')*1);
	int currm = ((buffer[5] - '0')*10 + (buffer[6] - '0')*1);
	int currd = ((buffer[0] - '0')*1);

	// nothing for Sundays
	if(currd == 0) {
		text_layer_set_text(just_words, "Obligations in:");
		snprintf(text, sizeof(text), "a while...");
	}

	// for Mondays, Wednesdays, and Fridays
	else if(currd == 1 || currd == 3 || currd == 5) {
    // ENGR 210 Circuits
		if ((currh > 6 && currh <= 9) || (currh == 9 && currm < 30)) {
			int value = 30 - currm + 60 * (9 - currh);
			snprintf(text, sizeof(text), "%d min!",value);
			text_layer_set_text(just_words, "Circuits in:");
		}
		else if (currh < 10 || (currh == 10 && currm < 20)) {
			int value = 20 - currm + 60 * (10 - currh);
			snprintf(text, sizeof(text), "%d min!",value);
			text_layer_set_text(just_words, "Class ends in:");
		}
    // Java Office Hours Wed
		else if (currd == 3 && (currh < 10 || (currh == 10 && currm < 30))) {
			int value = 30 - currm + 60*(10 - currh);
			snprintf(text, sizeof(text), "%d min!",value);
			text_layer_set_text(just_words, "Office Hours in:");
		}
		else if (currd == 3 && (currh < 11 || (currh == 11 && currm < 30))) {
			int value = 30 - currm + 60 * (11 - currh);
			snprintf(text, sizeof(text), "%d min!",value);
			text_layer_set_text(just_words, "Times up in:");
		}
    // EECS 338 OS
		else if (currh < 14 || (currh == 14 && currm < 15)) {
			int value = 15 - currm + 60*(14 - currh);
			snprintf(text, sizeof(text), "%d min!",value);
			text_layer_set_text(just_words, "EECS338 in:");
		}
		else if (currh < 15 || (currh == 15 && currm < 5)) {
			int value = 5 - currm + 60 * (15 - currh);
			snprintf(text, sizeof(text), "%d min!",value);
			text_layer_set_text(just_words, "Class ends in:");
		}
    // Java TA Meeting Mondays
		else if (currd == 1 && (currh < 18 || (currh == 18 && currm < 20))) {
			int value = 20 - currm + 60*(18 - currh);
			snprintf(text, sizeof(text), "%d min!",value);
			text_layer_set_text(just_words, "Java TA Meeting in:");
		}
		else if (currd == 1 && currh == 18 && currm < 50) {
			int value = 50 - currm;
			snprintf(text, sizeof(text), "%d min!",value);
			text_layer_set_text(just_words, "TA Meeting ends in:");
		}
    // Java Recitation 1 Wed
    else if (currd == 3 && (currh < 15 || (currh == 15 && currm < 20))) {
			int value = 20 - currm + 60*(15 - currh);
			snprintf(text, sizeof(text), "%d min!",value);
			text_layer_set_text(just_words, "Java TA Lab 1 in:");
		}
		else if (currd == 3 && (currh < 16 || (currh == 16 && currm < 10))) {
			int value = 10 - currm + 60 * (16 - currh);;
			snprintf(text, sizeof(text), "%d min!",value);
			text_layer_set_text(just_words, "Java Lab 1 ends in:");
		}
    // Java Recitation 2 Wed
    else if (currd == 3 && currh == 16 && currm < 25) {
			int value = 25 - currm + 60 * (16 - currh);
			snprintf(text, sizeof(text), "%d min!",value);
			text_layer_set_text(just_words, "Java TA Lab 2 in:");
		}
		else if (currd == 3 && (currh < 17 || (currh == 17 && currm < 15))) {
			int value = 15 - currm + 60 * (17 - currh);
			snprintf(text, sizeof(text), "%d min!",value);
			text_layer_set_text(just_words, "Java Lab 2 ends in:");
		}
    // Turn in Circuits HW
    else if (currd == 3 && (currh < 23 || (currh == 23 && currm < 59))) {
			int value = 59 - currm + 60*(23 - currh);
			snprintf(text, sizeof(text), "%d min!",value);
			text_layer_set_text(just_words, "Circuits HW DUE in:");
		}
		else {
			snprintf(text, sizeof(text), "a while...");
			text_layer_set_text(just_words, "Obligations in:");
		}
	}

	// for Tuesdays and Thursdays
	else if(currd == 2 || currd == 4) {
    // EECS 290 Computer Gaming
		if ((currh > 6 && currh <= 8) || (currh == 8 && currm < 30)) {
			int value = 30 - currm + 60 * (8 - currh);
			snprintf(text, sizeof(text), "%d min!",value);
			text_layer_set_text(just_words, "EECS290 in:");
		}
		else if (currh < 9 || (currh == 9 && currm < 45)) {
			int value = 20 - currm + 60 * (10 - currh);
			snprintf(text, sizeof(text), "%d min!",value);
			text_layer_set_text(just_words, "Class ends in:");
		}
    // EECS 391 Artificial Intelligence
		else if (currh < 10 || (currh == 10 && currm < 0)) {
			int value = 0 - currm + 60*(10 - currh);
			snprintf(text, sizeof(text), "%d min!",value);
			text_layer_set_text(just_words, "EECS 391 AI in:");
		}
		else if (currh < 11 || (currh == 11 && currm < 15)) {
			int value = 15 - currm + 60 * (11 - currh);
			snprintf(text, sizeof(text), "%d min!",value);
			text_layer_set_text(just_words, "Class ends in:");
		}
    // ENGR 210 Circuits Lab Tues
		else if (currd == 2 && (currh < 14 || (currh == 14 && currm < 30))) {
			int value = 30 - currm + 60*(14 - currh);
			snprintf(text, sizeof(text), "%d min!",value);
			text_layer_set_text(just_words, "Circuits Lab in:");
		}
		else if (currd == 2 && (currh < 16 || (currh == 16 && currm < 30))) {
			int value = 30 - currm + 60 * (16 - currh);
			snprintf(text, sizeof(text), "%d min!",value);
			text_layer_set_text(just_words, "Lab ends in:");
		}
    // Turn in OS HW on Tues
    else if (currd == 2 && (currh < 23 || (currh == 23 && currm < 0))) {
			int value = 0 - currm + 60*(23 - currh);
			snprintf(text, sizeof(text), "%d min!",value);
			text_layer_set_text(just_words, "OS HW DUE in:");
		}
		else {
			snprintf(text, sizeof(text), "a while...");
			text_layer_set_text(just_words, "Obligations in:");
		}
	}

	else {
		snprintf(text, sizeof(text), "a while...");
    text_layer_set_text(just_words, "Obligations in:");
	}

}

static void main_window_load(Window *window) {

	// Create background
	background_layer = text_layer_create(GRect(0, 0, 144, 200));
	text_layer_set_background_color(background_layer, GColorPurpureus);

	// Create time TextLayer
	s_time_layer = text_layer_create(GRect(4, 5, 136, 40));
	text_layer_set_background_color(s_time_layer, GColorCyan);
	text_layer_set_text_color(s_time_layer, GColorBlack);
	text_layer_set_text(s_time_layer, "");

	just_words = text_layer_create(GRect(0, 50, 144, 50));
	text_layer_set_background_color(just_words, GColorBlack);
	text_layer_set_text_color(just_words, GColorWhite);

	min_left = text_layer_create(GRect(0, 100, 144, 80));
	text_layer_set_background_color(min_left, GColorBlack);
	text_layer_set_text_color(min_left, GColorWhite);
	text_layer_set_text(min_left, "");

	// Improve the layout to be more like a watchface
	text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
	text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
	text_layer_set_font(just_words, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_text_alignment(just_words, GTextAlignmentCenter);
	text_layer_set_font(min_left, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
	text_layer_set_text_alignment(min_left, GTextAlignmentCenter);

	// Add it as a child layer to the Window's root layer
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(background_layer));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(just_words));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(min_left));


	// Make sure the time is displayed from the start
	update_time();
}

static void main_window_unload(Window *window) {
	// Destroy TextLayer
	text_layer_destroy(background_layer);
	text_layer_destroy(s_time_layer);
	text_layer_destroy(just_words);
	text_layer_destroy(min_left);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
	update_time();
}

static void init() {
	// Create main Window element and assign to pointer
	s_main_window = window_create();

	// Set handlers to manage the elements inside the Window
	window_set_window_handlers(s_main_window, (WindowHandlers) {
		.load = main_window_load,
				.unload = main_window_unload
	});

	// Show the Window on the watch, with animated=true
	window_stack_push(s_main_window, true);

	// Register with TickTimerService
	tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
	// Destroy Window
	window_destroy(s_main_window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}