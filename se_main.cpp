

#include "global.hpp"

#include "base_gl.hpp"
#include "base_sdl.hpp"
#include "load_image.hpp"

#include "maps.hpp"
#include "creature.hpp"
#include "camera.hpp"
#include "trigger.hpp"


// To avoid the game running too fast.
const int fastest_fps(40);

/**
 * Draw everthing need, the background, the map 
 * and the creatures.
 */
static void draw_screen(void);
/**
 * Get the keyboard state and pay back to the down keys.
 * Control the moving of the given character.
 * Control the camera.
 */
static void kb_control(Creature *curr);

// Just the normal value. 
int width = 1024;
int height = 768;

OffsetCamera *camera;
GameMap *m;
Creature *fleur;
GLuint bg;

/**
 * The main method, entry of the game.
 * Init everything, then run the main loop.
 * Controls FPS and the game logic.
 */
int main(int argc, char* argv[])
{
    // Init the aborting module, SDL, GL, and textures.
    std::set_unexpected(aborting_unexpected);
    setup_sdl_for_gl(argc, argv);
    setup_opengl();
    load_images();
    
    // Init things to be displayed.
    camera = new OffsetCamera(90.0);
    bg = get_texture("night.jpg");
    // m = new GameMap("maps$scpark");
    m = new GameMap("maps$street");
	m->add_trigger(new CameraTrigger<OffsetCamera>(3.9598, -48.7598, 10.0, 0.0, camera));
	m->add_trigger(new CameraTrigger<OffsetCamera>(24.9026, -16.0620, 6.5, 180.0, camera));
    fleur = new Creature("Fleur Coleman", "fleur", m, -1.4, -19.6, 296.795);
    fleur->add_action(ext_a_running, 23, 7);
    
    while (1) {
        // Control the fps of the game.
        int tick_at_start = SDL_GetTicks();
        
        process_events();
        kb_control(fleur);
		m->test_triggers(fleur, false);
        draw_screen();
        
        // Control the fps of the game.
        int tick_gone = SDL_GetTicks() - tick_at_start;
        if (fastest_fps > tick_gone)
        {
            SDL_Delay(fastest_fps - tick_gone);
        }
    }
    return 0;
}

/**
 * Draw everthing need, the background, the map 
 * and the creatures.
 */
static void draw_screen(void)
{
    start_drawing();
    draw_fullscreen(bg);
    start_gl_3d(true);
    camera->set_up(fleur);
    m->draw();
    fleur->draw();
    SDL_GL_SwapBuffers();
}

/**
 * Quit on ESC pressed.
 */
void handle_key_down(SDL_keysym* keysym)
{
    switch(keysym->sym) {
        case SDLK_ESCAPE:
        quit_game();
        break;
        #ifdef __DEBUG
        case SDLK_n:
        camera->turn(90.0);
        break;
        #endif
        default:
        break;
    }
}

/**
 * Get the keyboard state and pay back to the down keys.
 * Control the moving of the given character.
 * Control the camera.
 */
static void kb_control(Creature *curr)
{
    Uint8 *k = SDL_GetKeyState(NULL);
    // Character.
    double m_r = camera->get_real_angle();
    bool moving = false;
    if (k[SDLK_w])
    {
        if (k[SDLK_a])
        {
            m_r -= 45.0;
        } else if (k[SDLK_d]) {
            m_r += 45.0;
        } else {
            m_r += 0.0;
        }
        moving = true;
    } else if (k[SDLK_s])
    {
        if (k[SDLK_a])
        {
            m_r -= 135.0;
        } else if (k[SDLK_d]) {
            m_r += 135.0;
        } else {
            m_r += 180.0;
        }
        moving = true;
    } else if (k[SDLK_a])
    {
        m_r -= 90.0;
        moving = true;
    } else if (k[SDLK_d])
    {
        m_r += 90.0;
        moving = true;
    }
    if (moving)
    {
        curr->move_rotated(m_r, 0.7);
        curr->do_action(ext_a_running);
    } else {
        curr->do_action("");
    }
    // Camera.
    if (k[SDLK_j])
    {
        camera->upper();
    }
    if (k[SDLK_l])
    {
        camera->lower();
    }
    if (k[SDLK_u])
    {
        camera->nearer();
    }
    if (k[SDLK_o])
    {
        camera->farther();
    }
    #ifdef __DEBUG
    if (k[SDLK_b])
    {
        fleur->dump_debug();
    }
    #endif
}

