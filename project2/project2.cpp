// Project 2: Color and Image Classes
// Programmer: [Your Name]
// Date: [Approximate Date]
// Purpose: Implement classes to represent colors, images, and pixel locations.

#include <iostream>
using namespace std;

// Constants for color range
const int COLOR_MIN = 0;
const int COLOR_MAX = 1000;

// Class to represent a color
class ColorClass {
private:
    int red;
    int green;
    int blue;

    // Helper function to clip color values to the valid range
    int clipValue(int value) {
        if (value < COLOR_MIN) {
            return COLOR_MIN;
        } else if (value > COLOR_MAX) {
            return COLOR_MAX;
        }
        return value;
    }

public:
    // Default constructor: sets color to full white
    ColorClass() : red(COLOR_MAX), green(COLOR_MAX), blue(COLOR_MAX) {}

    // Value constructor: sets color to specified values, clipping if necessary
    ColorClass(int inRed, int inGreen, int inBlue) {
        red = clipValue(inRed);
        green = clipValue(inGreen);
        blue = clipValue(inBlue);
    }

    // Set color to black
    void setToBlack() {
        red = COLOR_MIN;
        green = COLOR_MIN;
        blue = COLOR_MIN;
    }

    // Set color to red
    void setToRed() {
        red = COLOR_MAX;
        green = COLOR_MIN;
        blue = COLOR_MIN;
    }

    // Set color to green
    void setToGreen() {
        red = COLOR_MIN;
        green = COLOR_MAX;
        blue = COLOR_MIN;
    }

    // Set color to blue
    void setToBlue() {
        red = COLOR_MIN;
        green = COLOR_MIN;
        blue = COLOR_MAX;
    }

    // Set color to white
    void setToWhite() {
        red = COLOR_MAX;
        green = COLOR_MAX;
        blue = COLOR_MAX;
    }

    // Set color to specified values, clipping if necessary
    bool setTo(int inRed, int inGreen, int inBlue) {
        int newRed = clipValue(inRed);
        int newGreen = clipValue(inGreen);
        int newBlue = clipValue(inBlue);

        bool clipped = (newRed != inRed) || (newGreen != inGreen) || (newBlue != inBlue);

        red = newRed;
        green = newGreen;
        blue = newBlue;

        return clipped;
    }

    // Set color to the same as another ColorClass object
    bool setTo(const ColorClass &inColor) {
        red = inColor.red;
        green = inColor.green;
        blue = inColor.blue;
        return false; // No clipping needed since inColor is already clipped
    }

    // Add another color to this color
    bool addColor(const ColorClass &rhs) {
        int newRed = red + rhs.red;
        int newGreen = green + rhs.green;
        int newBlue = blue + rhs.blue;

        bool clipped = setTo(newRed, newGreen, newBlue);
        return clipped;
    }

    // Subtract another color from this color
    bool subtractColor(const ColorClass &rhs) {
        int newRed = red - rhs.red;
        int newGreen = green - rhs.green;
        int newBlue = blue - rhs.blue;

        bool clipped = setTo(newRed, newGreen, newBlue);
        return clipped;
    }

    // Adjust brightness by multiplying each component by a factor
    bool adjustBrightness(double adjFactor) {
        int newRed = static_cast<int>(red * adjFactor);
        int newGreen = static_cast<int>(green * adjFactor);
        int newBlue = static_cast<int>(blue * adjFactor);

        bool clipped = setTo(newRed, newGreen, newBlue);
        return clipped;
    }

    // Print the color's component values
    void printComponentValues() const {
        cout << "R: " << red << " G: " << green << " B: " << blue;
    }
};

// Class to represent a pixel location
class RowColumnClass {
private:
    int row;
    int col;

public:
    // Default constructor: sets row and column to -99999
    RowColumnClass() : row(-99999), col(-99999) {}

    // Value constructor: sets row and column to specified values
    RowColumnClass(int inRow, int inCol) : row(inRow), col(inCol) {}

    // Set row and column values
    void setRowCol(int inRow, int inCol) {
        row = inRow;
        col = inCol;
    }

    // Set row value
    void setRow(int inRow) {
        row = inRow;
    }

    // Set column value
    void setCol(int inCol) {
        col = inCol;
    }

    // Get row value
    int getRow() const {
        return row;
    }

    // Get column value
    int getCol() const {
        return col;
    }

    // Add another RowColumnClass to this one
    void addRowColTo(const RowColumnClass &inRowCol) {
        row += inRowCol.row;
        col += inRowCol.col;
    }

    // Print the row and column values
    void printRowCol() const {
        cout << "[" << row << "," << col << "]";
    }
};

// Class to represent an image
class ColorImageClass {
private:
    static const int IMAGE_ROWS = 10;
    static const int IMAGE_COLS = 18;
    ColorClass image[IMAGE_ROWS][IMAGE_COLS];

public:
    // Default constructor: sets all pixels to black
    ColorImageClass() {
        initializeTo(ColorClass(COLOR_MIN, COLOR_MIN, COLOR_MIN));
    }

    // Initialize all pixels to the specified color
    void initializeTo(const ColorClass &inColor) {
        for (int i = 0; i < IMAGE_ROWS; i++) {
            for (int j = 0; j < IMAGE_COLS; j++) {
                image[i][j].setTo(inColor);
            }
        }
    }

    // Add another image to this image
    bool addImageTo(const ColorImageClass &rhsImg) {
        bool clipped = false;
        for (int i = 0; i < IMAGE_ROWS; i++) {
            for (int j = 0; j < IMAGE_COLS; j++) {
                if (image[i][j].addColor(rhsImg.image[i][j])) {
                    clipped = true;
                }
            }
        }
        return clipped;
    }

    // Add multiple images to this image
    bool addImages(int numImgsToAdd, const ColorImageClass imagesToAdd[]) {
        bool clipped = false;
        for (int i = 0; i < numImgsToAdd; i++) {
            if (addImageTo(imagesToAdd[i])) {
                clipped = true;
            }
        }
        return clipped;
    }

    // Set the color of a specific pixel
    bool setColorAtLocation(const RowColumnClass &inRowCol, const ColorClass &inColor) {
        int row = inRowCol.getRow();
        int col = inRowCol.getCol();

        if (row >= 0 && row < IMAGE_ROWS && col >= 0 && col < IMAGE_COLS) {
            image[row][col].setTo(inColor);
            return true;
        }
        return false;
    }

    // Get the color of a specific pixel
    bool getColorAtLocation(const RowColumnClass &inRowCol, ColorClass &outColor) const {
        int row = inRowCol.getRow();
        int col = inRowCol.getCol();

        if (row >= 0 && row < IMAGE_ROWS && col >= 0 && col < IMAGE_COLS) {
            outColor.setTo(image[row][col]);
            return true;
        }
        return false;
    }

    // Print the entire image
    void printImage() const {
        for (int i = 0; i < IMAGE_ROWS; i++) {
            for (int j = 0; j < IMAGE_COLS; j++) {
                image[i][j].printComponentValues();
                if (j < IMAGE_COLS - 1) {
                    cout << "--";
                }
            }
            cout << endl;
        }
    }
};

// Special testing requirement
#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main() {
    ColorClass testColor;
    RowColumnClass testRowCol;
    RowColumnClass testRowColOther(111, 222);
    ColorImageClass testImage;
    ColorImageClass testImages[3];

    // Test some basic ColorClass operations...
    cout << "Initial: ";
    testColor.printComponentValues();
    cout << endl;

    testColor.setToBlack();
    cout << "Black: ";
    testColor.printComponentValues();
    cout << endl;

    testColor.setToGreen();
    cout << "Green: ";
    testColor.printComponentValues();
    cout << endl;

    testColor.adjustBrightness(0.5);
    cout << "Dimmer Green: ";
    testColor.printComponentValues();
    cout << endl;

    // Test some basic RowColumnClass operations...
    cout << "Want defaults: ";
    testRowCol.printRowCol();
    cout << endl;

    testRowCol.setRowCol(2, 8);
    cout << "Want 2,8: ";
    testRowCol.printRowCol();
    cout << endl;

    cout << "Want 111, 222: ";
    testRowColOther.printRowCol();
    cout << endl;

    testRowColOther.setRowCol(4, 2);
    testRowCol.addRowColTo(testRowColOther);
    cout << "Want 6,10: ";
    testRowCol.printRowCol();
    cout << endl;

    // Test some basic ColorImageClass operations...
    testColor.setToRed();
    testImage.initializeTo(testColor);

    testRowCol.setRowCol(555, 5);
    cout << "Want: Color at [555,5]: Invalid Index!" << endl;
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor)) {
        testColor.printComponentValues();
    } else {
        cout << "Invalid Index!";
    }
    cout << endl;

    testRowCol.setRow(4);
    cout << "Want: Color at [4,5]: R: 1000 G: 0 B: 0" << endl;
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor)) {
        testColor.printComponentValues();
    } else {
        cout << "Invalid Index!";
    }
    cout << endl;

    // Set up an array of images of different colors
    testColor.setToRed();
    testColor.adjustBrightness(0.25);
    testImages[0].initializeTo(testColor);
    testColor.setToBlue();
    testColor.adjustBrightness(0.75);
    testImages[1].initializeTo(testColor);
    testColor.setToGreen();
    testImages[2].initializeTo(testColor);

    // Modify a few individual pixel colors
    testRowCol.setRowCol(4, 2);
    testColor.setToWhite();
    testImages[1].setColorAtLocation(testRowCol, testColor);

    testRowCol.setRowCol(2, 4);
    testColor.setToBlack();
    testImages[2].setColorAtLocation(testRowCol, testColor);

    // Add up all images in testImages array and assign result to the testImage image
    testImage.addImages(3, testImages);

    // Check some certain values
    cout << "Added values:" << endl;
    for (int colInd = 0; colInd < 8; colInd += 2) {
        testRowCol.setRowCol(4, colInd);
        cout << "Color at ";
        testRowCol.printRowCol();
        cout << ": ";
        if (testImage.getColorAtLocation(testRowCol, testColor)) {
            testColor.printComponentValues();
        } else {
            cout << "Invalid Index!";
        }
        cout << endl;
    }

    for (int rowInd = 0; rowInd < 8; rowInd += 2) {
        testRowCol.setRowCol(rowInd, 4);
        cout << "Color at ";
        testRowCol.printRowCol();
        cout << ": ";
        if (testImage.getColorAtLocation(testRowCol, testColor)) {
            testColor.printComponentValues();
        } else {
            cout << "Invalid Index!";
        }
        cout << endl;
    }

    cout << "Printing entire test image:" << endl;
    testImage.printImage();

    return 0;
}
#endif
