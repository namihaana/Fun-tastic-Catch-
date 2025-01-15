/*
16 Jan, 2025
added about us image
added button click sounds
*/


#include "iGraphics.h"
#include <windows.h> //sounds 16jan

// Screen size
int screenSizeX = 1000;
int screenSizeY = 800;

// Background images
int menuBg, aboutUsBg, highScoreBg;

// Button properties
struct Button {
	int x, y;
	int width, height;
	bool isHovered;
} buttons[4];

// Button labels
char* buttonLabels[] = { "Play", "High Score", "About Us", "Exit" };

// Back button properties (for all screens)
struct Button backButton = { 20, screenSizeY-75, 200, 50, false };

// Current screen state
enum Screen { MENU, PLAY, HIGH_SCORE, ABOUT_US };
Screen currentScreen = MENU;

// Initialize button positions and sizes
void initializeButtons() {
	int buttonWidth = 200;
	int buttonHeight = 50;
	int startX = (screenSizeX - buttonWidth) / 2;
	int startY = 400;

	for (int i = 0; i < 4; i++) {
		buttons[i].x = startX;
		buttons[i].y = startY - i * (buttonHeight + 20);
		buttons[i].width = buttonWidth;
		buttons[i].height = buttonHeight;
		buttons[i].isHovered = false;
	}
}

//back button 16jan
void drawBackButton() {
	if (currentScreen != MENU) {
		// Draw button background
		if (backButton.isHovered) {
			iSetColor(0, 102, 204);  // Hover color next page
			iFilledRectangle(backButton.x - 10, backButton.y - 5, backButton.width + 20, backButton.height + 10);
		}
		else {
			iSetColor(86, 164, 230);   // Normal color
			iFilledRectangle(backButton.x, backButton.y, backButton.width, backButton.height);
		}

		// Center the text
		iSetColor(255, 255, 255);  // White text

		int textWidth = 8 * strlen("Back"); // Approximate text width
		int textX = backButton.x + (backButton.width - textWidth) / 2;

		int textHeight = 12; // Approximate text height for HELVETICA_18
		int textY = backButton.y + (backButton.height - textHeight) / 2;

		// Shadow and hover effect
		// Draw "Back" text
		if (backButton.isHovered) {
			iText(textX, textY, "Back", GLUT_BITMAP_9_BY_15); // Larger font on hover
		}
		else {
			iText(textX, textY, "Back", GLUT_BITMAP_8_BY_13); // Smaller font when not hovered
		}

	}
}

// Draw the main menu screen 16 jan
void drawMenu() {
	iClear();
	iShowImage(0, 0, screenSizeX, screenSizeY, menuBg);

	for (int i = 0; i < 4; i++) {
		Button btn = buttons[i];

		// Draw button background
		if (btn.isHovered) {
			iSetColor(0, 102, 204);  // Hover color
			iFilledRectangle(btn.x - 10, btn.y - 5, btn.width + 20, btn.height + 10);
		}
		else {
			iSetColor(86, 164, 230);   // Normal color
			iFilledRectangle(btn.x, btn.y, btn.width, btn.height);
		}

		// Draw button text
		iSetColor(255, 255, 255);  // White text

		// Calculate centered text position
		int textWidth = 8 * strlen(buttonLabels[i]); // Approximate width per character
		int textX = btn.x + (btn.width - textWidth) / 2;

		int textHeight = 12; // Approximate text height for HELVETICA_18
		int textY = btn.y + (btn.height - textHeight) / 2;

		// Add bold effect when hovered
		if (btn.isHovered) {
			iText(textX, textY, buttonLabels[i], GLUT_BITMAP_9_BY_15);
		}
		else {
			iText(textX, textY, buttonLabels[i], GLUT_BITMAP_8_BY_13
				);
		}
	}
}


// Draw the "About Us" screen 16 jan
void drawAboutUs() {
	iClear();
	iShowImage(0, 0, screenSizeX, screenSizeY, aboutUsBg);
	// Draw the title
	int titleWidth = 12 * strlen("About Us");
	int titleX = (screenSizeX - titleWidth) / 2;
	int titleY = screenSizeY - 100;  // Slightly below the top

	iSetColor(255, 255, 255);
	iText(titleX, titleY, "About Us", GLUT_BITMAP_9_BY_15); //next pg chng

	drawBackButton();
}

// Draw the "High Score" screen
void drawHighScore() {
	iClear();
	iShowImage(0, 0, screenSizeX, screenSizeY, highScoreBg);
	
	drawBackButton();
}

// Draw the "Play" screen (Game screen, could be just a placeholder for now)
void drawPlay() {
	iClear();


}

// Main drawing function
void iDraw() {
	if (currentScreen == MENU) {
		drawMenu();
	}
	else if (currentScreen == ABOUT_US) {
		drawAboutUs();
	}
	else if (currentScreen == HIGH_SCORE) {
		drawHighScore();
	}
	else if (currentScreen == PLAY) {
		drawPlay();
	}
}

// Handle passive mouse movement to check if the cursor is over a button
void iPassiveMouseMove(int mx, int my) {
	for (int i = 0; i < 4; i++) {
		if (mx >= buttons[i].x && mx <= buttons[i].x + buttons[i].width &&
			my >= buttons[i].y && my <= buttons[i].y + buttons[i].height) {
			buttons[i].isHovered = true;
		}
		else {
			buttons[i].isHovered = false;
		}
	}

	// Check if the mouse is hovering over the back button
	if (mx >= backButton.x && mx <= backButton.x + backButton.width &&
		my >= backButton.y && my <= backButton.y + backButton.height) {
		backButton.isHovered = true;
	}
	else {
		backButton.isHovered = false;
	}
}

// Handle mouse clicks for navigation 16 jan
void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (int i = 0; i < 4; i++) {
			if (mx >= buttons[i].x && mx <= buttons[i].x + buttons[i].width &&
				my >= buttons[i].y && my <= buttons[i].y + buttons[i].height) {

				// Play sound when a button is clicked
				PlaySound("button sound.wav", NULL, SND_ASYNC);
			
				// Handle button clicks to change screens
				if (i == 0) {
					currentScreen = PLAY;  // Start the game
				}
				else if (i == 1) {
					currentScreen = HIGH_SCORE;  // Show high scores
				}
				else if (i == 2) {
					currentScreen = ABOUT_US;  // Show about us information
				}
				else if (i == 3) {
					exit(0);  // Exit the game
				}
			}
		}
		// 
		// Back to Menu (for "About Us" and "High Score" screens)
		if (currentScreen == ABOUT_US || currentScreen == HIGH_SCORE || currentScreen == PLAY) {
			if (mx >= backButton.x && mx <= backButton.x + backButton.width &&
				my >= backButton.y && my <= backButton.y + backButton.height) {

				// Play sound when the back button is clicked
				PlaySound("button sound.wav", NULL, SND_ASYNC);

				currentScreen = MENU;  // Go back to the main menu
			}
		}
	}
}


void iMouseMove(int mx, int my) {
	// Empty function to handle mouse dragging
}

void iKeyboard(unsigned char key) {
	if (key == '\r') {
		printf("Enter key pressed!\n");
	}
	if (key == 'p') {
		printf("P key pressed - Game paused!\n");
	}
}

void iSpecialKeyboard(unsigned char key) {
	if (key == GLUT_KEY_RIGHT) {
		printf("Right arrow key pressed!\n");
	}
	if (key == GLUT_KEY_LEFT) {
		printf("Left arrow key pressed!\n");
	}
	if (key == GLUT_KEY_UP) {
		printf("Up arrow key pressed!\n");
	}
	if (key == GLUT_KEY_DOWN) {
		printf("Down arrow key pressed!\n");
	}
	if (key == GLUT_KEY_HOME) {
		printf("Home key pressed!\n");
	}
}


int main() {
	iInitialize(screenSizeX, screenSizeY, "Fun-tastic Catch!");

	// Load background images
	menuBg = iLoadImage("menu_bg.png");
	aboutUsBg = iLoadImage("about us.png");
	highScoreBg = iLoadImage("menu_bg.png");

	initializeButtons();
	iStart();
	return 0;
}
