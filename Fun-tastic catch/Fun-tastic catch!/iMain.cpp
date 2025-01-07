#include "iGraphics.h"

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

//back button
void drawBackButton(){
	
	if (currentScreen != MENU){
		if (backButton.isHovered) {
			iSetColor(61, 111, 255);  // Hover color
			iFilledRectangle(backButton.x - 10, backButton.y - 5, backButton.width + 20, backButton.height + 10);
		}
		else {
			iSetColor(86, 164, 230);   // Normal color
			iFilledRectangle(backButton.x, backButton.y, backButton.width, backButton.height);
		}
		iSetColor(255, 255, 255);  // White text
		if (backButton.isHovered) {
			iText(backButton.width / 2, backButton.y + backButton.height / 2 - 5, "Back", GLUT_BITMAP_HELVETICA_18);
		}
		else {
			iText(backButton.width /2, backButton.y+ backButton.height /2-5, "Back", GLUT_BITMAP_HELVETICA_12);
		}
	}
}
// Draw the main menu screen
void drawMenu() {
	iClear();
	iShowImage(0, 0, screenSizeX, screenSizeY, menuBg);

	for (int i = 0; i < 4; i++) {
		Button btn = buttons[i];

		// Button background
		if (btn.isHovered) {
			iSetColor(61, 111, 255);  // Hover color
			iFilledRectangle(btn.x - 10, btn.y - 5, btn.width + 20, btn.height + 10);
		}
		else {
			iSetColor(86, 164, 230);   // Normal color
			iFilledRectangle(btn.x, btn.y, btn.width, btn.height);
		}

		// Button text color
		iSetColor(255, 255, 255);  // White text

		// Center text in button
		int textWidth = 10 * strlen(buttonLabels[i]);  // Approximate width per character
		int textX = btn.x + (btn.width - textWidth) / 2;
		int textY = btn.y + (btn.height / 2) - 5;

		// Bold effect when hovered
		if (btn.isHovered) {
			iText(textX, textY, buttonLabels[i], GLUT_BITMAP_HELVETICA_18);
		}
		else {
			iText(textX, textY, buttonLabels[i], GLUT_BITMAP_HELVETICA_12);
		}
	}

	
}

// Draw the "About Us" screen
void drawAboutUs() {
	iClear();
	iShowImage(0, 0, screenSizeX, screenSizeY, aboutUsBg);

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

// Handle mouse clicks for navigation
void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (int i = 0; i < 4; i++) {
			if (mx >= buttons[i].x && mx <= buttons[i].x + buttons[i].width &&
				my >= buttons[i].y && my <= buttons[i].y + buttons[i].height) {
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

		// Back to Menu (for "About Us" and "High Score" screens)
		if (currentScreen == ABOUT_US || currentScreen == HIGH_SCORE || currentScreen == PLAY) {
			if (mx >= backButton.x && mx <= backButton.x + backButton.width &&
				my >= backButton.y && my <= backButton.y + backButton.height) {
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
	aboutUsBg = iLoadImage("menu_bg.png");
	highScoreBg = iLoadImage("menu_bg.png");

	initializeButtons();
	iStart();
	return 0;
}
