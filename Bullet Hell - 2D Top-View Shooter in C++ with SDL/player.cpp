#pragma warning (disable : 26812 )

#include"player.h"
#include"texturemanager.h"

Player::Player(SDL_Renderer* renderer) {
    // Load textures
    tex_left = TextureManager::loadTexture("./media/Player/Character_left.bmp", true,renderer);
    tex_right = TextureManager::loadTexture("./media/Player/Character_right.bmp", true, renderer);
    tex_up = TextureManager::loadTexture("./media/Player/Character_up.bmp", true, renderer);
    tex_down = TextureManager::loadTexture("./media/Player/Character_down.bmp", true, renderer);
    bullet_texture_left = TextureManager::loadTexture("./media/Player/bullet_left.bmp", true, renderer);
    bullet_texture_right = TextureManager::loadTexture("./media/Player/bullet_right.bmp", true, renderer);
    bullet_texture_up = TextureManager::loadTexture("./media/Player/bullet_up.bmp", true, renderer);
    bullet_texture_down = TextureManager::loadTexture("./media/Player/bullet_down.bmp", true, renderer);
    invicibility_tex = TextureManager::loadTexture("./media/Player/invicibility.bmp", true, renderer);
    hearth_tex = TextureManager::loadTexture("./media/Player/hearth.bmp", true, renderer);
    // Set movement parameters
    pos = Point(LEVEL_WIDTH / 2, LEVEL_HEIGHT / 2);
    vel_x = 0;
    vel_y = 0;
    // Create Hitbox
    hitbox = { 0,0,ENTITY_SIZE,ENTITY_SIZE };
    // Set up render properties
    src = { 0,0,ENTITY_SIZE,ENTITY_SIZE };
    dest = { 0,0,ENTITY_SIZE,ENTITY_SIZE };
    // Setting up animations
    direction = IDLE; // Starting state
    current_frame = 0; // Reset frame counter on start
    current_texture = tex_down; // Idle texture is the one facing down
    current_animation_frame = 0; // Start from first frame
    health_bar_dest = { HP_BAR_RENDER_OFFSET,HP_BAR_RENDER_OFFSET,hearth_size,hearth_size };
    health_bar_src = { 0,0,hearth_size,hearth_size };
    // Shooting
    bullet_src = { 0,0,bullet_size,bullet_size };
    bullet_hitbox = { pos.x,pos.y,bullet_size,bullet_size };
    shooting = false;
    shooting_start = 0;
    shooting_direction = DOWN;
    current_bullet_texture = bullet_texture_down;
    bullet_speed = 20;
    moving_and_shooting = false;
    hp = hp_amount;
    recently_hit = false;
}

void Player::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) //If a key was pressed
    { 
        switch (e.key.keysym.sym)
        {
        case SDLK_UP: 
            moving_and_shooting = true;
            vel_y -= PLAYER_VEL; 
            shooting_direction = UP; 
            current_bullet_texture = bullet_texture_up;
            break;
        case SDLK_DOWN:
            moving_and_shooting = true;
            vel_y += PLAYER_VEL;
            shooting_direction = DOWN;
            current_bullet_texture = bullet_texture_down;
            break;
        case SDLK_LEFT: 
            moving_and_shooting = true;
            vel_x -= PLAYER_VEL;
            shooting_direction = LEFT;
            current_bullet_texture = bullet_texture_left;

            break;
        case SDLK_RIGHT: 
            moving_and_shooting = true;
            vel_x += PLAYER_VEL;
            shooting_direction = RIGHT;
            current_bullet_texture = bullet_texture_right;
            break;
        case SDLK_SPACE: // shoot
                shooting_start = SDL_GetTicks();
                shooting = true;
            break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) //If a key was released
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP: 
            vel_y += PLAYER_VEL;
            moving_and_shooting = false;
            break;
        case SDLK_DOWN:
            vel_y -= PLAYER_VEL; 
            moving_and_shooting = false;
            break;
        case SDLK_LEFT: 
            vel_x += PLAYER_VEL;
            moving_and_shooting = false;
            break;
        case SDLK_RIGHT: 
            vel_x -= PLAYER_VEL;
            moving_and_shooting = false;
            break;
        }
    }
}

void Player::shoot() {
    if (moving_and_shooting) bullet_speed = bullet_speed_moving; // Adjust bullet velocity
    else bullet_speed = bullet_speed_moving;
    switch (shooting_direction) {
    case LEFT:
        bullet_hitbox.x -= bullet_speed;
        break;
    case UP:
        bullet_hitbox.y -= bullet_speed;
        break;
    case DOWN:
        bullet_hitbox.y += bullet_speed;
        break;
    case RIGHT:
        bullet_hitbox.x += bullet_speed;
        break;
    }
}

void Player::renderShoot(SDL_Renderer* renderer, int cam_x, int cam_y) {
    // Subtract offset
    if (shooting) {
        bullet_hitbox.x -= cam_x;
        bullet_hitbox.y -= cam_y;
        TextureManager::drawTexture(current_bullet_texture, bullet_src, bullet_hitbox, renderer);
        // Add offset
        bullet_hitbox.x += cam_x;
        bullet_hitbox.y += cam_y;
    }
}

void Player::renderHealthBar(SDL_Renderer* renderer, int cam_x, int cam_y) {
    health_bar_dest.x = HP_BAR_RENDER_OFFSET;
    health_bar_dest.y = HP_BAR_RENDER_OFFSET;
    for (int i = 0; i < hp; i++) {
        TextureManager::drawTexture(hearth_tex, health_bar_src, health_bar_dest, renderer);  
        health_bar_dest.x += hearth_size;
    }
}


void Player::move() 
{
    Point old_pos = pos; // Save position pre move
    pos.x += vel_x;
    if ((pos.x < 0) || (pos.x + ENTITY_SIZE > LEVEL_WIDTH))
    {
        pos.x -= vel_x; //Move back
    }
    pos.y += vel_y;
    if ((pos.y < 0) || (pos.y + ENTITY_SIZE > LEVEL_HEIGHT))
    {
        pos.y -= vel_y; //Move back
    }
    // Determine direction for choosing an animation and load correct texture
    direction = determineDirection(old_pos,pos);
    current_texture = chooseTexture(direction);
    if (shooting) {
        if (shooting_start + shooting_time > SDL_GetTicks()) shoot();
        else {
            bullet_hitbox.x = pos.x;
            bullet_hitbox.y = pos.y;
            shooting = false;
        }
    }
}

bool Player::handleCollsiion(SDL_Rect* bullets,int bullets_amount) {
    if (!checkCollision(bullets, bullets_amount)) { // Didn't collied
        dest.x = pos.x; // Update render destination
        dest.y = pos.y;
        hitbox.x = pos.x; // Update Hitbox
        hitbox.y = pos.y;
        return false;
    }
    else { // Collided 
        return true;
    }
}

bool Player::checkCollision(SDL_Rect* projectiles, int bullets_amount) {
    if (recently_hit) {
        if (hit_start + HIT_INVICIBILITY_TIME_PLAYER < SDL_GetTicks()) recently_hit = false;
    }
    else {
        for (int i = 0; i < bullets_amount; i++) {
            SDL_Rect res;
            if (SDL_IntersectRect(&projectiles[i], &hitbox, &res) == SDL_TRUE) { // Check for intersections
                recently_hit = true;
                hp--;
                hit_start = SDL_GetTicks();
                return true;
            }
        }
    }
    return false;
}

Dir Player::determineDirection(Point old_pos,Point new_pos) {
    if (new_pos.x < old_pos.x) return LEFT;
    else if (new_pos.x > old_pos.x) return RIGHT;
    else if (new_pos.y < old_pos.y) return UP;
    else if (new_pos.y > old_pos.y) return DOWN;
    else return IDLE; // Player didn't move
}

SDL_Texture* Player::chooseTexture(Dir direction) {
    if (recently_hit) return invicibility_tex;
    switch (direction) {
    case LEFT:
        return tex_left;
        break;
    case RIGHT:
        return tex_right;
        break;
    case UP:
        return tex_up;
        break;
    case DOWN:
        return tex_down;
        break; 
    default:
        return tex_down;
        break;
    }
}

void Player::render(SDL_Renderer* renderer,int cam_x,int cam_y) { 
    if (direction != IDLE) { // If player moves 
        if (!recently_hit) {
            animate(); // Cycle through animation frames 
            src.x = current_animation_frame * ENTITY_SIZE; // Load next animation frames
        }
    }
    else src.x = 0; // Idle static frame [0]
    dest.x -= cam_x; // Adjust relative to camera
    dest.y -= cam_y;
    TextureManager::drawTexture(current_texture, src, dest,renderer); // Render
    renderShoot(renderer,cam_x,cam_y);
    renderHealthBar(renderer, cam_x, cam_y);
}

void Player::animate() {
    current_frame++; // Count frames 
    if (current_frame + 1 == animation_frames) { // Load up next animation every 4th frame
        current_animation_frame++; // Increment currently rendered frame 
        if (current_animation_frame == animation_frames) current_animation_frame = 0; // Reset animation cycle
        current_frame = 0; // Reset counter 
    }
}

Player::~Player() {
    SDL_DestroyTexture(tex_left);
    SDL_DestroyTexture(tex_right);
    SDL_DestroyTexture(tex_up);
    SDL_DestroyTexture(tex_down);
    SDL_DestroyTexture(bullet_texture_left);
    SDL_DestroyTexture(bullet_texture_right);
    SDL_DestroyTexture(bullet_texture_up);
    SDL_DestroyTexture(bullet_texture_down);
    SDL_DestroyTexture(invicibility_tex);
    SDL_DestroyTexture(hearth_tex);
}