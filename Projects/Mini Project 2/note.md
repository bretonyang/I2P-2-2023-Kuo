# Notes for Project 2

## Set Up Project Build Options

### Settings

Go to `Project > Build options ...`

- Select the project name on the left side.

  - Select `Search directories > Compiler` and click `Add`, paste the following path and click `OK`:

    ```
    C:\allegro\include\
    ```

  - Select `Search directories > Linker` and click `Add`, paste the following path and click `OK`:

    ```
    C:\allegro\lib\
    ```

- Select `Debug` on the left side.

  Select `Linker settings`, click `Add`, paste the following path, and click `OK`:

  ```
  C:\allegro\lib\liballegro_monolith-debug.dll.a
  ```

- Select `Release` on the left side.

  Select `Linker settings`, click `Add`, paste the following path, and click `OK`:

  ```
  C:\allegro\lib\liballegro_monolith.dll.a
  ```

- Click `OK` to confirm all above settings.

### Test the library

- Copy and paste the following code to out `main.c` at `Projects > Workspace > [ProjectName](allegro-test) > Sources > main.c`.

  ```c
  #include <allegro5/allegro.h>
  #include <allegro5/allegro_font.h>
  int main(int argc, char **argv) {
      al_init();
      al_init_font_addon();
      ALLEGRO_DISPLAY* display = al_create_display(800, 600);
      ALLEGRO_FONT* font = al_create_builtin_font();
      al_clear_to_color(al_map_rgb(0, 0, 0));
      al_draw_text(font, al_map_rgb(255, 255, 255), 400, 300, ALLEGRO_ALIGN_CENTER, "Welcome to Allegro!");
      al_flip_display();
      al_rest(5.0);
      al_destroy_font(font);
      al_destroy_display(display);
      return 0;
  }
  ```

- Press `F9` to compile and run, there should be a pop out window saying "Welcome to Allegro!".

- If an `dll not found` error occurred, copy the file from the below path to `[Project Directory]\bin\Debug`.

  ```
  C:\allegro\bin\allegro_monolith-debug-5.2.dll
  ```

---

## Hackathon TODOs

1. Settings scene and slider effect
2. Add a "DiceOneEnemy", which should be faster than RedNormalEnemy
3. - New turret "MachineGunTurret" with new bullet "FireBullet", which can slow down enemy for 50% for 5 seconds.
   - add "W" key for buying new turret(still waiting for placement tho).
   - Shooting range increased to 300
4. Add effect "ShootingEffect" for PlugGunTurret.
5. Press "tab" to toggle debug mode, and "↑↓←→←→" + "ENTER" for cheat mode (plane fly through and an explosion that destroys all enemies, money += 10000)
6. Find bug in win scene

```txt
2 3 4
1 2.5 5
0 2 1
2 1 5
0 2 1
2 2.5 10
0 6 1
1 1 1
0 2 1
1 2.5 20
0 12 1
2 1 5
0 2 1
1 2.5 20
0 12 1
1 1 10
0 2 1
2 1 1
0 2 1
2 2.5 10
```
