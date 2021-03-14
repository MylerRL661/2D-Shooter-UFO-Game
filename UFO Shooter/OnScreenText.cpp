/**
* @author Benjamin Williams <bwilliams@lincoln.ac.uk> Modified by Phil Carlisle pcarlisle@lincoln.ac.uk
*
* @brief  A file which uses SDL_TTF to render text to the screen.
* @notes  Consult the lecture slides for the usage of this class.
*/
//#include "stdafx.h"

//Include header file for definitions & prototypes
#include "OnScreenText.h"

//Define RGBA mask for later on, depending on if SDL is storing colours in little/big endian format
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define RMASK 0xff000000
#define GMASK 0x00ff0000
#define BMASK 0x0000ff00
#define AMASK 0x000000ff
#else
#define RMASK 0x000000ff
#define GMASK 0x0000ff00
#define BMASK 0x00ff0000
#define AMASK 0xff000000
#endif

/// <summary>
/// Called when this instance has been initialised.
/// </summary>
ScreenText::ScreenText(SDL_Window* window, const std::string& path, int fontsize)
{
	//Set window and renderer
	this->window = window;
	this->renderer = SDL_GetRenderer(window);
	this->fontScale = fontsize;

	//Couldn't open font data
	if (!loadFontData(path))
	{
		//Log error message and return
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't open font file '%s' or read data.", path);
		return;
	}

}


/// <summary>
/// Called when this instance has been destroyed.
/// </summary>
ScreenText::~ScreenText(void)
{
	//  fontptr wasn't NULL, so release the font, set its pointer to null 
	if (fontptr != NULL)
	{
		TTF_CloseFont(fontptr);
		fontptr = NULL;
	}

	//Destroy existing surfaces and textures
	SDL_FreeSurface(this->textSurface);

	//If the texture is not null.. destroy it
	if (this->textTexture != NULL)
		SDL_DestroyTexture(this->textTexture);
}


/// <summary>
/// Updates and remakes the surface after any state changes.
/// </summary>
void ScreenText::updateSurface(void)
{
	//Do a bit of cheating, remake surface with same string.. updating it :)
	this->setText(this->text);
}


/// <summary>
/// Creates an text surface.. destroys existing textures and surfaces too.
/// </summary>
void ScreenText::createTextSurface(void)
{
	if (fontptr == NULL) return;
	//Destroy existing surfaces and textures
	if (this->textSurface != NULL)
		SDL_FreeSurface(this->textSurface);

	//If the texture is not null.. destroy it
	if (this->textTexture != NULL)
		SDL_DestroyTexture(this->textTexture);

	// renders the text via SDL_TTF into a surface, then loads that into a texture
	// note: uncomment the various lines below one at a time to see the difference
	//SDL_Surface * textSurface = TTF_RenderText_Shaded(fontptr, text.c_str(), color, backgroundcolour);
	SDL_Surface * textSurface = TTF_RenderText_Blended(fontptr, text.c_str(), color);
	//SDL_Surface * textSurface = TTF_RenderText_Solid(fontptr, text.c_str(), color);

	if (textSurface != NULL)
	{
		width = textSurface->w;
		height = textSurface->h;

		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (!textTexture)
		{
			SDL_Log("Unable to create SDL_Texture in ScreenText::CreateTextSurface");
		}
		SDL_FreeSurface(textSurface);
		textSurface = NULL;
	}
	else
	{
		SDL_Log("Unable to create SDL_Surface in ScreenText::CreateTextSurface");
	}



}


/// <summary>
/// Renders the text to screen.
/// </summary>
void ScreenText::render(void)
{
	//Source rect is the full width of the text
	SDL_Rect src = { 0, 0, this->width, this->height };

	//Dest rect is using internal state of this ScreenText instance
	SDL_Rect dst = { this->x, this->y, this->width, this->height };

	//Use rendercopy to copy using these parameters
	SDL_RenderCopy(renderer, this->textTexture, &src, &dst);
}


/// <summary>
/// Sets the colour of the text to rendered.
/// </summary>
/// <param name="color">The RGB_888 integer representing a colour.</param>
void ScreenText::setColor(unsigned int color)
{
	//Extract R G and B channels, mask with 0xff
	unsigned char
		r = (color >> 16) & 0xff,
		g = (color >> 8) & 0xff,
		b = (color >> 0) & 0xff;

	//Set the colour
	this->setColor(r, g, b);
}

/// <summary>
/// Sets the colour of the text to rendered.
/// </summary>
/// <param name="r">The r component [0, 255].</param>
/// <param name="g">The g component [0, 255].</param>
/// <param name="b">The b component [0, 255].</param>
void ScreenText::setColor(unsigned char r, unsigned char g, unsigned char b)
{
	//Make a new colour
	SDL_Color color = { r, g, b };

	//Call other overloaded setColor function
	this->setColor(color);
}


/// <summary>
/// Sets the colour of the text to rendered.
/// </summary>
/// <param name="color">The colour.</param>
void ScreenText::setColor(SDL_Color color)
{
	//Set up colour
	this->color = color;

	//Update surface
	this->updateSurface();
}


/// <summary>
/// Moves the text to another place on screen.
/// </summary>
/// <param name="x">The x position.</param>
/// <param name="y">The y position.</param>
void ScreenText::move(int x, int y)
{
	//Set internal x and y
	this->x = x;
	this->y = y;
}

/// <summary>
/// Sets the text, along with the x, y position and font size.
/// </summary>
/// <param name="text">The text.</param>
/// <param name="posX">The x position.</param>
/// <param name="posY">The y position.</param>
/// <param name="fontSize">The font size.</param>
/// <param name="r">The red component.</param>
/// <param name="g">The green component.</param>
/// <param name="b">The blue component.</param>
void ScreenText::setText(const std::string& text, const int posX, const int posY, const bool bCenterText, const int fontSize, const int r, const int g, const int b)
{
	//Set x, y and font scale
	this->x = posX;
	this->y = posY;

	// this will reload font from TTF file for the right font point size if needed
	setFontSize(fontSize);

	//If parameters have been changed
	if (r != -1 && g != -1 && b != -1)
		this->setColor(r, g, b);

	//Call set text normally
	setText(text);

	// if bCenterText is true, then our X,Y is meant to be the position of the center of the text (so we can use it centered on screen)
	// so in this case, compute the new X and Y position based on the size of the text surface created with this text output (surface)
	if (bCenterText)
	{
		this->x = posX - (width * 0.5);
		this->y = posY - (height * 0.5);
	}

}


/// <summary>
/// Sets the text to render before render() is called. This prepares the texture to render from
/// </summary>
/// <param name="path">The text.</param>
void ScreenText::setText(const std::string& text)
{
	//Set text!
	this->text = text;

	//Create text surface
	createTextSurface();
}

void ScreenText::setFontSize(const int fontSize)
{
	if (fontSize != fontScale)
	{
		fontScale = fontSize;
		// font size requested has changed.. so we need to reload the TTF_Font pointer with the font at the correct point size via the loadFontData method
		loadFontData(fontpath);
		// and recreate the render surfaces
		createTextSurface();
	}
}

/// <summary>
/// Loads font data from a given path and saves it into this instance.
/// </summary>
/// <param name="path">The path.</param>
bool ScreenText::loadFontData(const std::string& path)
{
	fontpath = path;
	//Log to tell the user we're starting
	SDL_Log("Font loading started! Path is '%s'", fontpath.c_str());

	//  fontptr wasn't NULL, so release the old font, set its pointer to null and then call loadFontData
	if (fontptr != NULL)
	{
		TTF_CloseFont(fontptr);
		fontptr = NULL;
	}

	//Try to open up the file 
	fontptr = TTF_OpenFont(fontpath.c_str(), fontScale);

	//Couldn't be opened. Return false.
	if (!fontptr)
		return false;

	//Return true -- everything is good!
	return true;
}