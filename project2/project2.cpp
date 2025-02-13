// ============================================================
// Project 2: Color and Image Classes
// Programmer: Md Arifuzzaman Faisal
// Date: 12 February 2025
// Purpose: Implement classes to represent colors, 
// images, and pixel locations.
// ============================================================

// Library includes
#include <iostream>
using namespace std;

// Constant declarations and initializations
const int COLOR_MIN_VALUE = 0;
const int COLOR_MAX_VALUE = 1000;
// Default sets for row and column to -99999
const int DEFAULT_ROW_COLUMN_VALUE = -99999;
// For ColorImageClass
const int IMAGE_ROWS = 10;
const int IMAGE_COLS = 18;
// for loop start point
const int START_POINT = 0;

// Class to represent a color
class ColorClass {
    int red;
    int green;
    int blue;

    // Helper function to clip color values 
    // to the valid range
    int clipValue(int value);

    public:
    // Default constructor: sets color to full white
    ColorClass();

    // Value constructor: sets color to specified values, 
    // clipping if necessary
    ColorClass(
        const int inRed, 
        const int inGreen, 
        const int inBlue
        );

    // Set color to black
    void setToBlack();

    // Set color to red
    void setToRed();

    // Set color to green
    void setToGreen();

    // Set color to blue
    void setToBlue();

    // Set color to white
    void setToWhite();

    // Set color to specified values, 
    // clipping if necessary
    bool setTo(
        const int inRed, 
        const int inGreen, 
        const int inBlue
        );

    // Set color to the same as another ColorClass object
    bool setTo(
        const ColorClass &inColor
        );

    // Add another color to this color    
    bool addColor(
        const ColorClass &rhs
        );

    // Subtract another color from this color
    bool subtractColor(
        const ColorClass &rhs
        );

    // Adjust brightness by multiplying each 
    //component by a factor
    bool adjustBrightness(
        const double adjFactor
        );

    // Print the color's component values
    void printComponentValues() const;
};

// Class to represent a pixel location
class RowColumnClass {
    int row;
    int col;

    public:
    // Default constructor: sets row and column to -99999
    RowColumnClass();

    // Value constructor: sets row and column 
    //to specified values
    RowColumnClass(
        const int inRow,
        const int inCol
        );

    // Set row and column values
    void setRowCol(
        const int inRow,
        const int inCol
        );

    // Set row value
    void setRow(
        const int inRow
        );

    // Set column value
    void setCol(
        const int inCol
        );

    // Get row value
    int getRow() const;

    // Get column value
    int getCol() const;

    // Add another RowColumnClass to this one
    void addRowColTo(
        const RowColumnClass &inRowCol
        );

    // Print the row and column values
    void printRowCol() const;
};

// Class to represent an image
class ColorImageClass {

    ColorClass image[IMAGE_ROWS][IMAGE_COLS];

    public:
    // Default constructor: sets all pixels to black
    ColorImageClass();

    // Initialize all pixels to the specified color
    void initializeTo(
        const ColorClass &inColor
        );

    // Add another image to this image
    bool addImageTo(
        const ColorImageClass &rhsImg
        );

    // Add multiple images to this image
    bool addImages(
        const int numImgsToAdd, 
        const ColorImageClass imagesToAdd[]
        );

    // Set the color of a specific pixel
    bool setColorAtLocation(
        const RowColumnClass &inRowCol,
        const ColorClass &inColor
        );

    // Get the color of a specific pixel
    bool getColorAtLocation(
        const RowColumnClass &inRowCol,
        ColorClass &outColor
        ) const;

    // Print the entire image
    void printImage() const;
};

// Main function

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main()
{
    ColorClass testColor;
    RowColumnClass testRowCol;
    RowColumnClass testRowColOther(111, 222);
    ColorImageClass testImage;
    ColorImageClass testImages[3];

    //Test some basic ColorClass operations...
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

    //Test some basic RowColumnClass operations...
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

    //Test some basic ColorImageClass operations...
    testColor.setToRed();
    testImage.initializeTo(testColor);

    testRowCol.setRowCol(555, 5);
    cout << "Want: Color at [555,5]: Invalid Index!" << endl;
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
    {
        testColor.printComponentValues();
    }
    else
    {
        cout << "Invalid Index!";
    }
    cout << endl;

    testRowCol.setRow(4);
    cout << "Want: Color at [4,5]: R: 1000 G: 0 B: 0" << endl;
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
    {
        testColor.printComponentValues();
    }
    else
    {
        cout << "Invalid Index!";
    }
    cout << endl;

    //Set up an array of images of different colors
    testColor.setToRed();
    testColor.adjustBrightness(0.25);
    testImages[0].initializeTo(testColor);
    testColor.setToBlue();
    testColor.adjustBrightness(0.75);
    testImages[1].initializeTo(testColor);
    testColor.setToGreen();
    testImages[2].initializeTo(testColor);

    //Modify a few individual pixel colors
    testRowCol.setRowCol(4, 2);
    testColor.setToWhite();
    testImages[1].setColorAtLocation(testRowCol, testColor);

    testRowCol.setRowCol(2, 4);
    testColor.setToBlack();
    testImages[2].setColorAtLocation(testRowCol, testColor);

    //Add up all images in testImages array and assign result
    //to the testImage image
    testImage.addImages(3, testImages);
    
    //Check some certain values
    cout << "Added values:" << endl;
    for (int colInd = 0; colInd < 8; colInd += 2)
    {
        testRowCol.setRowCol(4, colInd);
        cout << "Color at ";
        testRowCol.printRowCol();
        cout << ": ";
        if (testImage.getColorAtLocation(testRowCol, testColor))
        {
        testColor.printComponentValues();
        }
        else
        {
        cout << "Invalid Index!";
        }
        cout << endl;
    }
    
    for (int rowInd = 0; rowInd < 8; rowInd += 2)
    {
        testRowCol.setRowCol(rowInd, 4);
        cout << "Color at ";
        testRowCol.printRowCol();
        cout << ": ";
        if (testImage.getColorAtLocation(testRowCol, testColor))
        {
        testColor.printComponentValues();
        }
        else
        {
        cout << "Invalid Index!";
        }
        cout << endl;
    }
    
    cout << "Printing entire test image:" << endl;
    testImage.printImage();

    return 0;
}
#endif



// --------All Methods Related to Corresponding Class----------
// -------------ColorClass Method Implementations -------------

/*
 Clips the given value to ensure it stays within range.
 Parameters:
 - value: Integer color value to be clipped.
 Returns: Clipped value within COLOR_MIN and COLOR_MAX_VALUE.
 */
int ColorClass::clipValue(int value) {
    if (value < COLOR_MIN_VALUE) {
        return COLOR_MIN_VALUE;
    } else if (value > COLOR_MAX_VALUE) {
        return COLOR_MAX_VALUE;
    }
    return value;
}

/*
 * Default constructor initializes color to white.
 */
ColorClass::ColorClass() : red(COLOR_MAX_VALUE), 
green(COLOR_MAX_VALUE), blue(COLOR_MAX_VALUE) {}

/*
 * Constructor initializes color with given values.
 * 
 * Parameters:
 *  - inRed, inGreen, inBlue: RGB color values.
 */
ColorClass::ColorClass(
    const int inRed, 
    const int inGreen, 
    const int inBlue
    ) {
    red = clipValue(inRed);
    green = clipValue(inGreen);
    blue = clipValue(inBlue);
}

/*
 * Sets the color to black (0,0,0).
 */
void ColorClass::setToBlack() {
    red = COLOR_MIN_VALUE;
    green = COLOR_MIN_VALUE;
    blue = COLOR_MIN_VALUE;
}

/*
 * Sets the color to red (max,0,0).
 */
void ColorClass::setToRed() {
    red = COLOR_MAX_VALUE;
    green = COLOR_MIN_VALUE;
    blue = COLOR_MIN_VALUE;
}

/*
 * Sets the color to green (0,max,0).
 */
void ColorClass::setToGreen() {
    red = COLOR_MIN_VALUE;
    green = COLOR_MAX_VALUE;
    blue = COLOR_MIN_VALUE;
}

/*
 * Sets the color to blue (0,0,max).
 */
void ColorClass::setToBlue() {
    red = COLOR_MIN_VALUE;
    green = COLOR_MIN_VALUE;
    blue = COLOR_MAX_VALUE;
}

/*
 * Sets the color to white (max,max,max).
 */
void ColorClass::setToWhite() {
    red = COLOR_MAX_VALUE;
    green = COLOR_MAX_VALUE;
    blue = COLOR_MAX_VALUE;
}

/*
Description: If any input value is outside the allowed
color value range, then the assigned value is "clipped" 
in order to keep the RGB color values within the valid
range. If any clipping was necessary, the function returns 
true, otherwise the function returns false.
 */
bool ColorClass::setTo(
    const int inRed, 
    const int inGreen, 
    const int inBlue
    ) {
    int newRed = clipValue(inRed);
    int newGreen = clipValue(inGreen);
    int newBlue = clipValue(inBlue);

    bool clipped = (newRed != inRed) || 
    (newGreen != inGreen) || (newBlue != inBlue);

    red = newRed;
    green = newGreen;
    blue = newBlue;

    return clipped;
}

/*
Function: setTo
Description: Copies color values from another ColorClass object.
Parameters:
- inColor: ColorClass object to copy values from.
Returns: 
- true if clipping is needed (though it should never happen),
- false otherwise.
*/
bool ColorClass::setTo(const ColorClass &inColor) {
    // Check if the input color values are within the valid range
    bool clipped = (inColor.red < COLOR_MIN_VALUE || 
                    inColor.red > COLOR_MAX_VALUE) ||
                   (inColor.green < COLOR_MIN_VALUE || 
                    inColor.green > COLOR_MAX_VALUE) ||
                   (inColor.blue < COLOR_MIN_VALUE || 
                    inColor.blue > COLOR_MAX_VALUE);
    // Assign the values regardless of clipping (since they should already be valid)
    if (!clipped) {
        red = inColor.red;
        green = inColor.green;
        blue = inColor.blue;
    }
    return clipped; 
}

/*
Function : addColor
 Description: Adds another color to this color and clips if needed.
Parameters:
- rhs: ColorClass object to add.
Returns true if clipping occurred, false otherwise.
 */
bool ColorClass::addColor(const ColorClass &rhs) {
    int newRed = red + rhs.red;
    int newGreen = green + rhs.green;
    int newBlue = blue + rhs.blue;

    bool clipped = setTo(newRed, newGreen, newBlue);
    return clipped;
}

/*
Function : subtractColor
Description: Subtracts another color from this color and 
clips if needed.
Parameters:
- rhs: ColorClass object to subtract.
Returns true if clipping occurred, false otherwise.
*/
bool ColorClass::subtractColor(const ColorClass &rhs) {
    int newRed = red - rhs.red;
    int newGreen = green - rhs.green;
    int newBlue = blue - rhs.blue;

    bool clipped = setTo(newRed, newGreen, newBlue);
    return clipped;
}

/*
Adjusts brightness using a scaling factor.
Parameters:
- adjFactor: Factor to scale the brightness.
Returns: - true if clipping occurred, false otherwise.
*/
bool ColorClass::adjustBrightness(const double adjFactor) {
    int newRed = (int)(red * adjFactor);
    int newGreen = (int)(green * adjFactor);
    int newBlue = (int)(blue * adjFactor);
    bool clipped = setTo(newRed, newGreen, newBlue);
    return clipped;
}

/*
Prints RGB values of the color.
*/
void ColorClass::printComponentValues() const {
    cout << "R: " << red << " G: " << green << " B: " << blue;
}

// -------------RowColumnClass Method Implementations -------------

/*
 * Default constructor initializes row and col values.
 */
RowColumnClass::RowColumnClass() : 
    row(DEFAULT_ROW_COLUMN_VALUE), col(DEFAULT_ROW_COLUMN_VALUE) {}

/*
Constructor initializes row and column with given values.
*/
RowColumnClass::RowColumnClass(const int inRow, const int inCol) : 
    row(inRow), col(inCol) {}

/*
Sets row and column values.
*/
void RowColumnClass::setRowCol(const int inRow, const int inCol) {
    row = inRow;
    col = inCol;
}

/*
 * Sets only the row value.
 */
void RowColumnClass::setRow(const int inRow) {
    row = inRow;
}

/*
 * Sets only the column value.
 */
void RowColumnClass::setCol(const int inCol) {
    col = inCol;
}

/*
 * Gets the row value.
 */
int RowColumnClass::getRow() const {
    return row;
}

/*
 * Gets the column value.
 */
int RowColumnClass::getCol() const {
    return col;
}

/*
 * Adds another RowColumnClass object to this object.
 */
void RowColumnClass::addRowColTo(const RowColumnClass &inRowCol) {
    row += inRowCol.row;
    col += inRowCol.col;
}

/*
 * Prints the row and column values.
 */
void RowColumnClass::printRowCol() const {
    cout << "[" << row << "," << col << "]";
}

// ------- ColorImageClass Method Implementations -------

/*
 Default constructor initializes image to black.
*/
ColorImageClass::ColorImageClass() {
    initializeTo(ColorClass(COLOR_MIN_VALUE, COLOR_MIN_VALUE, COLOR_MIN_VALUE));
}

/*
Description : Initializes the image with a specific color.
Parameters: - inColor: ColorClass object to fill the image.
*/
void ColorImageClass::initializeTo(const ColorClass &inColor) {
    for (int i = START_POINT; i < IMAGE_ROWS; i++) {
        for (int j = START_POINT; j < IMAGE_COLS; j++) {
            image[i][j].setTo(inColor);
        }
    }
}

/*
Function: addImageTo
 Description: Adds another image to this image.
 Parameters:
 *  - rhsImg: Image to add.
 Returns true if any pixel addition clips.
 */
bool ColorImageClass::addImageTo(const ColorImageClass &rhsImg) {
    bool clipped = false;
    for (int i = START_POINT; i < IMAGE_ROWS; i++) {
        for (int j = START_POINT; j < IMAGE_COLS; j++) {
            if (image[i][j].addColor(rhsImg.image[i][j])) {
                clipped = true;
            }
        }
    }
    return clipped;
}

/*
Function: addImages
Description: Adds multiple images together 
            and stores the result.
Parameters:
- numImgsToAdd: Number of images to be added.
- imagesToAdd[]: Array containing images to add.
Returns:
- true if any image addition causes clipping.
- false if no clipping occurs during the operation.
*/
bool ColorImageClass::addImages(const int numImgsToAdd, 
                                const ColorImageClass imagesToAdd[]
                                ) {
    
    // Initialize the image to black before adding
    ColorClass Initial;
    Initial.setToBlack();
    initializeTo(Initial); 
    
    // Flag to track if any clipping occurs
    bool clipped = false;

    // Iterate through all images to add them together
    for (int i = START_POINT; i < numImgsToAdd; i++) {
        bool imageClipped = addImageTo(imagesToAdd[i]);

        // If any image clips, set the flag to true
        if (imageClipped) {
            clipped = true;
        }
    }
    // Return whether clipping occurred
    return clipped;
}


/*
Function: setColorAtLocation
Description: Sets the color at a specific location 
    in the image.
Parameters:
- inRowCol: RowColumnClass object with row, col values.
- inColor: ColorClass object containing the new color.
Set the color and returns true if the location is 
within valid image bounds or return false if the location 
is out of bounds.
*/
bool ColorImageClass::setColorAtLocation(
                                        const RowColumnClass &inRowCol, 
                                        const ColorClass &inColor
                                        ) {
    
    int row = inRowCol.getRow(); // Get row index
    int col = inRowCol.getCol(); // Get column index

    // Check if row and column are within valid bounds
    if (row >= 0 && row < IMAGE_ROWS && 
        col >= 0 && col < IMAGE_COLS) {
        
        image[row][col].setTo(inColor); // Assign color
        return true; // Successful update
    }
    return false; // Location is out of bounds
}


/*
Function: getColorAtLocation
Decribtion: Retrieves the color at a given 
        location in the image.
Parameters:
- inRowCol: RowColumnClass object specifying location.
- outColor: ColorClass object to store retrieved color.

Returns true if the location is valid 
    false if the location is out of bounds.
 */
bool ColorImageClass::getColorAtLocation(
                                        const RowColumnClass &inRowCol, 
                                        ColorClass &outColor
                                    ) const {
    int row = inRowCol.getRow(); // Extract row index
    int col = inRowCol.getCol(); // Extract column index

    // Check if row and col are within valid image bounds
    if (row >= START_POINT && row < IMAGE_ROWS && 
    col >= START_POINT && col < IMAGE_COLS) {
    outColor.setTo(image[row][col]); // Set color at location
    return true; // Valid location
    }
    return false; // Out of bounds
}


/*
Function: printImage
Description: Prints the entire image stored in 
    the ColorImageClass object.
    Each pixel's component values are 
    printed and separated by "--".
*/
void ColorImageClass::printImage() const {
    // Loop through each row of the image
    for (int i = START_POINT; i < IMAGE_ROWS; i++) {
        // Loop through each column of the image
        for (int j = START_POINT; j < IMAGE_COLS; j++) {
            // Print the pixel's color component values
            image[i][j].printComponentValues();
            // Print separator between pixels, 
            // but not at the end of the row
            if (j < IMAGE_COLS - 1) {
                cout << "--";
            }
        }
        // Move to the next line after printing a row
        cout << endl;
    }
}
