#ifndef _IMAGE_H_
#define _IMAGE_H_
#include <GL/gl.h>
/*
 * Dve strukture koje opisuju strukturu dva zaglavlja
 * kojima pocinje svaka slika u bmp formatu.
 */

#define FLOOR "../../textures/ceil1.bmp"
#define CEILING "../../textures/ceil2.bmp"
#define LEFT_WALL "../../textures/lw4.bmp"
#define RIGHT_WALL "../../textures/lw4.bmp"
#define FRONT "../../textures/lw4.bmp"
#define BACK "../../textures/lw4.bmp"
#define DARTBOARD "../../textures/dartboard.bmp"

unsigned int textureNames[7];

//enables textures
void init_textures();
//disables textures
void unbind_texture();
//draws all textures
void draw_textures();
void draw_floor_texture();
void draw_left_wall_texture();
void draw_right_wall_texture();
void draw_front_wall_texture();
void draw_back_wall_texture();
void draw_ceiling_texture();
void draw_dartboard_texture();

//initializes textures w/out setting its coordinates
void set_texture(char* path, int i);
//initializes texture for dartboard
void set_transparent_texture(char* path, int i);

typedef struct {
  unsigned short type;
  unsigned int size;
  unsigned short reserved1;
  unsigned short reserved2;
  unsigned int offsetbits;
} BITMAPFILEHEADER;

typedef struct {
  unsigned int size;
  unsigned int width;
  unsigned int height;
  unsigned short planes;
  unsigned short bitcount;
  unsigned int compression;
  unsigned int sizeimage;
  int xpelspermeter;
  int ypelspermeter;
  unsigned int colorsused;
  unsigned int colorsimportant;
} BITMAPINFOHEADER;

/* Struktura za smestanje podataka o slici. */
typedef struct Image {
  int width, height; /* Dimenzije slike. */
  char *pixels; /* Niz u kojem se cuvaju podaci za sve piksele u obliku (R, G, B). */
} Image;

/* Funkcija koja inicijalizuje strukturu i vraca pokazivac na nju. */
Image *image_init(int width, int height);

/*
 * Funkcija koja oslobadja prostor u kojem su se cuvali
 * podaci o slici.
 */
void image_done(Image *image);

/*
 * Funkcija za ucitavanje podataka o slici koja se nalazi
 * u fajlu cije je ime filename u strukturu na koju pokazuje
 * image.
 */
void image_read(Image *image, char *filename);

Image* image;

#endif
