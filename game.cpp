#include "raylib.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>


bool touch_rec(Rectangle player, Rectangle enermy){
	return CheckCollisionRecs(player, enermy);	
}

bool shape_touch(Vector2 circle_pos, float circle_radius, Rectangle rect) {
    return CheckCollisionCircleRec(circle_pos, circle_radius, rect);
}

int getRandomNumber(int min, int max) {
    return min + (rand() % (max - min + 1));
}

int main() {
    InitWindow(1000, 800, "my_game");
    SetTargetFPS(60);

    srand(time(0)); 
	
	float enermy_x = 0;
	float enermy_y = 0;
	Rectangle enermy = {enermy_x,enermy_y,40,60};
	Rectangle text_box = {enermy_x,enermy_y,260,45};
	Rectangle death_screen = {0,0,10000,1600};
	float speed = 2.0;
    int score = 0;
    Rectangle rect = {400, 200, 40, 60};
    Vector2 coin = {(float)getRandomNumber(50, 950), (float)getRandomNumber(50, 750)};
    bool coin_exi = true;
	Vector2 bomb = {(float)getRandomNumber(50,950), (float)getRandomNumber(50,750)}; 
	bool bomb_exi = true;
    float circleRadius = 15;
	bool text_box_exi = false;
	bool show_message = false; 
	float message_start_time = 0.0f; 
	float message_duration = 3.0f;
	bool death = false;

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_W) && rect.y > 0 || IsKeyDown(KEY_UP) && rect.y > 0) rect.y -= 10;
        if (IsKeyDown(KEY_S) && rect.y + rect.height < 800|| IsKeyDown(KEY_DOWN) && rect.y + rect.height < 800) rect.y += 10;
        if (IsKeyDown(KEY_A) && rect.x > 0 || IsKeyDown(KEY_LEFT) && rect.x > 0) rect.x -= 10;
        if (IsKeyDown(KEY_D) && rect.x + rect.width < 1000|| IsKeyDown(KEY_RIGHT) && rect.x + rect.width < 1000) rect.x += 10;

        if (coin_exi && shape_touch(coin, circleRadius, rect)) {
            coin_exi = false;
            score += 1;
			speed += 0.1;
            coin = {(float)getRandomNumber(50, 950), (float)getRandomNumber(50, 750)};
            coin_exi = true;
        }

		if(bomb_exi && shape_touch(bomb,circleRadius,rect))
		{
			bomb_exi = false;
			if(score >= 5)
			{ 
				score -= 5;	
			}
			speed += 0.3;
			bomb = {(float)getRandomNumber(50,950),(float)getRandomNumber(50,750)};
			bomb_exi = true;
		}

		float dx = rect.x - enermy.x;
        float dy = rect.y - enermy.y;
        float length = sqrt(dx * dx + dy * dy);
		


        if (length != 0) {
            dx /= length;
            dy /= length;
        }

        enermy.x += dx * speed;
        enermy.y += dy * speed;
		text_box.x = enermy.x - 100; 
		text_box.y = enermy.y - 58;  
		
		if (touch_rec(rect, enermy)) 
		{ 
			show_message = true; message_start_time = GetTime(); 
		}

        BeginDrawing();
        ClearBackground(BLACK);
		
		
		
		DrawText(("Coins: " + std::to_string(score)).c_str(), 20, 20, 40, GREEN);
		
		if (coin_exi) {
			DrawCircleV(coin, circleRadius, YELLOW);
		}
		if(bomb_exi)
		{
			DrawCircleV(bomb,circleRadius,RED);
		}
        if (!touch_rec(rect,enermy)){
			DrawRectangleRec(rect, RED);
		}
	
				
			
		if(touch_rec(rect,enermy))
		{
			DrawRectangleRec(death_screen,BLACK);
			DrawText("you lose", 500,700, 60, RED);
			CloseWindow();

		}

		if (show_message) 
		{ 
			if (GetTime() - message_start_time < message_duration) 
			{ 
				DrawRectangleRec(text_box, WHITE); 
				DrawText("did you think that was it", text_box.x, text_box.y + 1, 20, BLACK); 
			} 
		}else 
		{
			show_message = false; 
		}
		
		DrawRectangleRec(enermy,BLUE);


        EndDrawing();
    }

    CloseWindow();
    return 0;
}

