#include <stdio.h>

#include <freetype/freetype.h>
#include <ft2build.h>

int main() {
  FT_Library  library;
  FT_Face     face = NULL;

  const char*  testdata_dir = getenv( "FREETYPE_TESTS_DATA_DIR" );
  char         filepath[FILENAME_MAX];


  snprintf( filepath, sizeof( filepath ), "%s/%s",
            testdata_dir ? testdata_dir : "./",
            "test.ttf" );

  FT_Init_FreeType( &library );
  if ( FT_New_Face( library, filepath, 0, &face ) != 0 )
  {
    fprintf( stderr, "Could not open file: %s\n", filepath );
    return 1;
  }

  printf("Loaded font: %s\n", filepath);


    if (FT_IS_SCALABLE(face))
        FT_Set_Pixel_Sizes(face, 0, 48);

   for ( FT_ULong  i = 65; i < 86; i++ )
   {
    FT_UInt   gid  = FT_Get_Char_Index( face, i );
    FT_Error  code = FT_Load_Glyph( face, gid, FT_LOAD_RENDER );


    printf("RENDERING CHARACTER %c\n\n", i);
    for (int y = 0; y < face->glyph->bitmap.rows; y++) {
        for(int x = 0; x < face->glyph->bitmap.width; x++) {
            if (face->glyph->bitmap.buffer[(y * face->glyph->bitmap.pitch) + x] == 0) {
                printf("-");
            } else {
                printf("#");
            }
        }

        printf("\n");
    }
   }

  return 0;
}
