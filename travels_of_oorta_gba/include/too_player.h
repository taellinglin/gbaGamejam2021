#ifndef TOO_PLAYER_H
#define TOO_PLAYER_H

#include "bn_fixed_point.h"
#include "bn_sprite_ptr.h"
#include "bn_camera_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_affine_bg_ptr.h"
#include "bn_span.h"
#include "bn_affine_bg_map_cell.h"

#include "too_level.h"
#include "too_hitbox.h"
#include "too_enemy.h"
#include "too_data.h"
#include "too_healthbar.h"
#include "too_spellbar.h"

#include "bn_sprite_items_cat_sprite.h"

namespace too
{
    class Player
    {
        private:
            bn::sprite_ptr _sprite;
            bn::sprite_ptr _tele_sprite;
            bn::fixed _dx;
            bn::fixed _dy;
            bn::fixed_point _pos;
            bn::optional<bn::camera_ptr> _camera;
            bn::sprite_ptr _text_bg1;
            bn::sprite_ptr _text_bg2;
            bn::sprite_ptr _skip;
            too::Healthbar _healthbar;
            too::Spellbar _spellbar;
            bn::sprite_text_generator _text_generator;

            //used for state management
            bool _jumping = false;
            bool _falling = false;
            bool _running = false;
            bool _wall_running;
            bool _listening = false;
            bool _grounded = false;
            bool _sliding = false;
            bool _already_running = false;
            bool _attacking = false;

            bool _glow_unlocked = true;

            bool _invulnerable = false;
            int _inv_timer = 0;

            bool _can_teleport = false;
            int _spell_selected= 0;


            Data _data;

            bn::optional<bn::span<const bn::affine_bg_map_cell>> _map_cells;
            bn::optional<bn::affine_bg_ptr> _map;
            bn::optional<bn::vector<Enemy,16>*> _enemies;

            too::Hitbox _hitbox_fall = Hitbox(0,16,16,0);
            too::Hitbox _hitbox_left = Hitbox(-8,0,8,16);
            too::Hitbox _hitbox_right = Hitbox(8,0,8,16);
            too::Hitbox _hitbox_jump = Hitbox(0,8,16,8);
            bn::sprite_animate_action<10> _action = bn::create_sprite_animate_action_forever(
                        _sprite, 10, bn::sprite_items::cat_sprite.tiles_item(), 0,1,0,1,0,1,0,1,0,1);
            bn::optional<bn::sprite_animate_action<4>> _spin_action;
            void _update_camera(int lerp);
            

        public:
            Player(bn::sprite_ptr sprite, bn::sprite_text_generator& text_generator);

            void hide();
            void show();
            Data data();
            
            [[nodiscard]] bn::fixed_point pos();

            void jump(bn::affine_bg_ptr map, too::Level level);
            void attack();
            void collide_with_objects(bn::affine_bg_ptr map, too::Level level);
            void collide_with_enemies();
            void move_right();
            void delete_data();
            void move_left();
            void check_attack();
            void set_healthbar_visibility(bool is_visible);
            void set_listening(bool is_listening);
            void set_can_teleport(bool can_teleport);
            void set_hp(int hp);
            int hp();
            bool is_listening();
            void apply_animation_state();
            void update_position(bn::affine_bg_ptr map, too::Level level);

            void spawn(bn::fixed_point pos, bn::camera_ptr camera, bn::affine_bg_ptr map, bn::vector<Enemy,16>& enemies);
            void reset();

            bool is_right();
    };
}

#endif