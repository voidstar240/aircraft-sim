#include "HW2_VISUALIZER.h"
#include <sstream>

HW2_VIZ::HW2_VIZ ()
{
  // returns zero on success else non-zero
  if ( SDL_Init ( SDL_INIT_EVERYTHING ) != 0 )
  {
    printf ( "error initializing SDL: %s\n", SDL_GetError () );
  }

  win = SDL_CreateWindow ( "Flight Management", // creates a window
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WIDTH, HEIGHT, 0 );
  renderer = SDL_CreateRenderer ( win, -1, 0 );
  image = SDL_LoadBMP ( "map.bmp" ); // this depends on where you run the binary file
  if (!image) {
    image = SDL_LoadBMP("assets/map.bmp");
    if (!image) {
      std::cout << "Unable to load map.bmp" << std::endl;
    }
  }
  texture = SDL_CreateTextureFromSurface ( renderer, image );
}

bool HW2_VIZ::update (double dt)
{
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT: {
          return false;
          break;
      }
      default: {
          break;
      }
    }
  }
  SDL_RenderCopy(renderer, texture, NULL, NULL);

  for ( auto itr = p_viz.planes_info.begin (); itr != p_viz.planes_info.end (); itr++ )
  {
    SDL_Vertex vertices[] = { itr->second.v1, itr->second.v2, itr->second.v3 };
    SDL_RenderGeometry ( renderer, texture, vertices, 3, NULL, 0 );
  }
  SDL_RenderPresent( renderer );

  SDL_Delay(dt);
  return true;
}

void HW2_VIZ::visualize_plane ( std::string airline, size_t origin, size_t des, double pos )
{
  // compute new triangle to draw
  SDL_Color  color = { 0, 0, 0, 255 };
  SDL_FPoint tex_coord = { 1, 1 };

  SDL_Vertex v0 = { {0, 0}, color, tex_coord };

  double x0 = p_viz.airport_location[origin].first;
  double y0 = p_viz.airport_location[origin].second;
  double x1 = p_viz.airport_location[des].first;
  double y1 = p_viz.airport_location[des].second;
  double d = sqrt ( ( x1 - x0 ) * ( x1 - x0 ) + ( y1 - y0 ) * ( y1 - y0 ) );
  double ratio = pos / d;
  v0.position.x = ( 1 - ratio ) * x0 + ratio * x1;
  v0.position.y = ( 1 - ratio ) * y0 + ratio * y1;

  std::stringstream origin_ss;
  origin_ss << origin;
  std::stringstream des_ss;
  des_ss << des;
  std::array<std::string, 3> key = { airline, origin_ss.str(), des_ss.str()};
  std::array<std::string, 3> key_temp = { airline, des_ss.str(), origin_ss.str() };

  if (p_viz.planes_info.find(key) == p_viz.planes_info.end() && p_viz.planes_info.find(key_temp) != p_viz.planes_info.end())
    key = key_temp;

  v0.color = p_viz.plane_colors[airline];

  p_viz.planes_info[key].v1 = v0;
  p_viz.planes_info[key].v2 = v0;
  p_viz.planes_info[key].v3 = v0;

  p_viz.planes_info[key].v1.position.y -= 15;
  p_viz.planes_info[key].v2.position.x -= 10;
  p_viz.planes_info[key].v2.position.y += 15;
  p_viz.planes_info[key].v3.position.x += 10;
  p_viz.planes_info[key].v3.position.y += 15;

  double heading = atan2 ( y1 - y0, x1 - x0 ) + 1.57079632679;
  double temp_x = 0;

  p_viz.planes_info[key].v1.position.x -= v0.position.x;
  p_viz.planes_info[key].v1.position.y -= v0.position.y;

  p_viz.planes_info[key].v2.position.x -= v0.position.x;
  p_viz.planes_info[key].v2.position.y -= v0.position.y;

  p_viz.planes_info[key].v3.position.x -= v0.position.x;
  p_viz.planes_info[key].v3.position.y -= v0.position.y;

  temp_x = p_viz.planes_info[key].v1.position.x;
  p_viz.planes_info[key].v1.position.x = temp_x * cos ( heading ) - p_viz.planes_info[key].v1.position.y * sin ( heading );
  p_viz.planes_info[key].v1.position.y = temp_x * sin ( heading ) + p_viz.planes_info[key].v1.position.y * cos ( heading );

  temp_x = p_viz.planes_info[key].v2.position.x;
  p_viz.planes_info[key].v2.position.x = temp_x * cos ( heading ) - p_viz.planes_info[key].v2.position.y * sin ( heading );
  p_viz.planes_info[key].v2.position.y = temp_x * sin ( heading ) + p_viz.planes_info[key].v2.position.y * cos ( heading );

  temp_x = p_viz.planes_info[key].v3.position.x;
  p_viz.planes_info[key].v3.position.x = temp_x * cos ( heading ) - p_viz.planes_info[key].v3.position.y * sin ( heading );
  p_viz.planes_info[key].v3.position.y = temp_x * sin ( heading ) + p_viz.planes_info[key].v3.position.y * cos ( heading );

  p_viz.planes_info[key].v1.position.x += v0.position.x;
  p_viz.planes_info[key].v1.position.y += v0.position.y;

  p_viz.planes_info[key].v2.position.x += v0.position.x;
  p_viz.planes_info[key].v2.position.y += v0.position.y;

  p_viz.planes_info[key].v3.position.x += v0.position.x;
  p_viz.planes_info[key].v3.position.y += v0.position.y;
}
