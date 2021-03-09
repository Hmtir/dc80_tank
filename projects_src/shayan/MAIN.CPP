
#include "classes.h"
#include "video.h"

void SplashScreen();
void Credit();
int MainMenu();
void GoPlay();

main()
{
 _VIDEO_INIT_DEVICE();
 SplashScreen();
 int menu;
 do
 {
  menu=MainMenu();
  switch(menu)
  {
   case 0: // Play Game
    GoPlay();
   break;

   case 1: // Credits
    Credit();
   break;
  }
 } while(menu!=2); // Exit Game

 _VIDEO_DEINIT_DEVICE();
return 0;
}
