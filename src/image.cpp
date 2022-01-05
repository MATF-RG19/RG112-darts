#include <cassert>
#include <cstdio>
#include <cstdlib>
#include "../include/image.h"



auto image_init(int width, int height) -> Image * {

  Image *image;

  /* U slucaju greske prekida se program. */
  assert(width >= 0 && height >= 0);

  /* Alocira se prostor za smestanje clanova strukture. */
  image = (Image *) malloc(sizeof(Image));
  assert(image != nullptr);

  /* Inicijlizuju se clanovi strukture. */
  image->width = width;
  image->height = height;
  if (width == 0 || height == 0)
    image->pixels = nullptr;
  else {
    image->pixels = (char *)malloc(3 * width * height * sizeof(char));
    assert(image->pixels != nullptr);
  }

  /* Vraca se pokazivac na inicijlizovanu strukturu. */
  return image;
}

void image_done(Image *image) {

  /*
   * Oslobadja se prostor za cuvanje podataka o pikselima
   * a potom se oslobadja i prostor u kojem su cuvani
   * podaci same strukture.
   */
  free(image->pixels);
  free(image);
}

void image_read(Image *image, char *filename) {

  FILE *file;
  BITMAPFILEHEADER bfh;
  BITMAPINFOHEADER bih;
  unsigned int i;
  unsigned char r, g, b, a;

  /* Brise se prethodni sadrzaj strukture Image. */
  free(image->pixels);
  image->pixels = nullptr;

  /* Otvara se fajl koji sadrzi sliku u binarnom rezimu. */
  assert((file = fopen(filename, "rb")) != nullptr);

  /* Ocitavaju se podaci prvog zaglavlja. */
  fread(&bfh.type, 2, 1, file);
  fread(&bfh.size, 4, 1, file);
  fread(&bfh.reserved1, 2, 1, file);
  fread(&bfh.reserved2, 2, 1, file);
  fread(&bfh.offsetbits, 4, 1, file);

  /* Ocitavaju se podaci drugog zaglavlja. */
  fread(&bih.size, 4, 1, file);
  fread(&bih.width, 4, 1, file);
  fread(&bih.height, 4, 1, file);
  fread(&bih.planes, 2, 1, file);
  fread(&bih.bitcount, 2, 1, file);
  fread(&bih.compression, 4, 1, file);
  fread(&bih.sizeimage, 4, 1, file);
  fread(&bih.xpelspermeter, 4, 1, file);
  fread(&bih.ypelspermeter, 4, 1, file);
  fread(&bih.colorsused, 4, 1, file);
  fread(&bih.colorsimportant, 4, 1, file);

  /*
   * Od podataka iz drugog zaglavlja koristimo samo informacije
   * o dimenzijama slike.
   */
  image->width = bih.width;
  image->height = bih.height;

  /*
   * U zavisnosti od toga koliko bitova informacija se cita po pikselu
   * (da li samo R, G i B komponenta ili R, G, B i A), alociramo niz
   * odgovarajuce duzine.
   */
  if (bih.bitcount == 24)
    image->pixels = (char *)malloc(3 * bih.width * bih.height * sizeof(char));
  else if (bih.bitcount == 32)
    image->pixels = (char *)malloc(4 * bih.width * bih.height * sizeof(char));
  else {
    fprintf(stderr, "image_read(): Podrzane su samo slike koje po pikselu cuvaju 24 ili 32 bita podataka.\n");
    exit(1);
  }
  assert(image->pixels != nullptr);

  /* Ucitavaju se podaci o pikselima i smestaju u alocirani niz. */
  if (bih.bitcount == 24)
    /*
     * Ako se po pikselu cita 24 bita = 3 bajta informacija, pretpostavljamo
     * da oni (ta 3 bajta) predstavljaju R, G i B komponentu boje (1 bajt po
     * komponenti).
     */
    for (i = 0; i < bih.width * bih.height; i++) {
      /*
       * Ovo mozda izgleda cudno, to sto se komponente boje citaju u suprotnom redosledu,
       * tj. prvo plava, pa zelena, pa crvena, ali tako pise u specifikaciji bmp formata.
       */
      fread(&b, sizeof(char), 1, file);
      fread(&g, sizeof(char), 1, file);
      fread(&r, sizeof(char), 1, file);

      image->pixels[3 * i] = r;
      image->pixels[3 * i + 1] = g;
      image->pixels[3 * i + 2] = b;
    }
  else if (bih.bitcount == 32)
    /*
     * Ako se po pikselu cita 32 bita = 4 bajta informacija, pretpostavljamo
     * da oni (ta 4 bajta) predstavljaju R, G, B i A komponentu boje (1 bajt po
     * komponenti).
     */
    for (i = 0; i < bih.width * bih.height; i++) {
      fread(&b, sizeof(char), 1, file);
      fread(&g, sizeof(char), 1, file);
      fread(&r, sizeof(char), 1, file);
      fread(&a, sizeof(char), 1, file);

      image->pixels[4 * i] = r;
      image->pixels[4 * i + 1] = g;
      image->pixels[4 * i + 2] = b;
      image->pixels[4 * i + 3] = a;
    }

  /* Zatvara se fajl. */
  fclose(file);
}

void init_textures(){

	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	image = image_init(0, 0);

	glGenTextures(7, textureNames);


}

void draw_textures(){
	draw_floor_texture();
	draw_left_wall_texture();
	draw_right_wall_texture();
	draw_front_wall_texture();
	draw_back_wall_texture();
	draw_ceiling_texture();
	draw_dartboard_texture();
}

void set_texture(char* path, int i){

	image_read(image, path);
	glBindTexture(GL_TEXTURE_2D, textureNames[i]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
}

void set_transparent_texture(char* path, int i){

	image_read(image, path);
	glBindTexture(GL_TEXTURE_2D, textureNames[i]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
}

void unbind_texture(){
	glBindTexture(GL_TEXTURE_2D, 0);
	image_done(image);
}

void draw_floor_texture(){
	glBindTexture(GL_TEXTURE_2D, textureNames[0]);
	glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);
		glTexCoord2f(0, 0);
		glVertex3f(92, -9.9, 130);

		glTexCoord2f(0, 1);
		glVertex3f(92, -9.9, -130);

		glTexCoord2f(1, 1);
		glVertex3f(-92, -9.9, -130);

		glTexCoord2f(1, 0);
		glVertex3f(-92, -9.9, 130);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

}

void draw_left_wall_texture() {
	glBindTexture(GL_TEXTURE_2D, textureNames[1]);
	glBegin(GL_QUADS);
		glNormal3f(1, 0, 0);
		glTexCoord2f(0, 0);
		glVertex3f(-91.9, -10, 130);

		glTexCoord2f(1, 0);
		glVertex3f(-91.9, -10, -130);

		glTexCoord2f(1, 1);
		glVertex3f(-91.9, 50, -130);

		glTexCoord2f(0, 1);
		glVertex3f(-91.9, 50, 130);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

}

void draw_right_wall_texture() {
	glBindTexture(GL_TEXTURE_2D, textureNames[2]);
	glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0);
		glTexCoord2f(0, 0);
		glVertex3f(91.9, -10, 129.9);

		glTexCoord2f(0, 1);
		glVertex3f(91.9, -10, -129.9);

		glTexCoord2f(1, 1);
		glVertex3f(91.9, 50, -129.9);

		glTexCoord2f(1, 0);
		glVertex3f(91.9, 50, 129.9);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

}

void draw_ceiling_texture() {
	glBindTexture(GL_TEXTURE_2D, textureNames[3]);
	glBegin(GL_QUADS);
		glNormal3f(0, -1, 0);
		glTexCoord2f(0, 0);
		glVertex3f(-92, 49.9, 130);

		glTexCoord2f(1, 0);
		glVertex3f(92, 49.9, 130);

		glTexCoord2f(1, 1);
		glVertex3f(92, 49.9, -130);

		glTexCoord2f(0, 1);
		glVertex3f(-92, 49.9, -130);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

}

void draw_front_wall_texture() {
	glBindTexture(GL_TEXTURE_2D, textureNames[4]);
	glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		glTexCoord2f(0, 0);
		glVertex3f(92, -10, -129.9);

		glTexCoord2f(0, 1);
		glVertex3f(-92, -10, -129.9);

		glTexCoord2f(1, 1);
		glVertex3f(-92, 50, -129.9);

		glTexCoord2f(1, 0);
		glVertex3f(92, 50, -129.9);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

}

void draw_back_wall_texture() {
	glBindTexture(GL_TEXTURE_2D, textureNames[5]);
	glBegin(GL_QUADS);
		glNormal3f(0, 0, -1);
		glTexCoord2f(0, 0);
		glVertex3f(-92, -10, 129.9);

		glTexCoord2f(0, 1);
		glVertex3f(92, -10, 129.9);

		glTexCoord2f(1, 1);
		glVertex3f(92, 50, 129.9);

		glTexCoord2f(1, 0);
		glVertex3f(-92, 50, 129.9);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

}

void draw_dartboard_texture() {

	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, textureNames[6]);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
		glTexCoord2f(.022, 0);
		glVertex3f(-9.3, 21.3, -126);

		glTexCoord2f(1.027, 0);
		glVertex3f(9.24, 21.3, -126);

		glTexCoord2f(1.027, 1);
		glVertex3f(9.24, 41, -126);

		glTexCoord2f(.022, 1);
		glVertex3f(-9.3, 41, -126);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_BLEND);

}
