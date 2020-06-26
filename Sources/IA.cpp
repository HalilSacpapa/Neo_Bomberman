#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <ostream>
#include <chrono>
#include <thread>

std::vector<std::vector<int>> g_path {};
int g_total {};
std::vector<std::vector<int>> g_map_bomb {};

bool is_free(int x, int y, const std::vector<std::vector<int>> &map, int i, int or_x, int or_y)
{
  if (x < 0) {
    return (false);
  } else if (x > 12)
    return (false);
  else if (y < 0) {
    return (false);
  } else if (y > 10)
    return (false);
  else if (map[x][y] != 0 && map[x][y] != 1) {
      if (map[x][y] == 2) {
        return (false);
      } else if (map[x][y] <= i) {
        return (false);
      }
  } else if (g_map_bomb[or_x][or_y] != -1 && g_map_bomb[x][y] == -1) {
    return (false);
  }
  return (true);
}

std::vector<std::vector<int>> rec_finding(int x_goal, int y_goal, std::vector<std::vector<int>> map, int x, int y, int i, int dir, std::vector<std::vector<int>> tmp_path, int tmp_total, const std::vector<std::vector<int>> &not_touchable_map)
{
  std::vector<int> tmp;
  for (; y != y_goal || x != x_goal;) {
    switch (dir) {
      case 0:
        if (is_free(x + 1, y, map, i, x, y) == true) {
          tmp.push_back(x+1);
          tmp.push_back(y);
          tmp_path.push_back(tmp);
          if (not_touchable_map[x+1][y] == 1) {
            tmp_total+=5;
          } else
            tmp_total++;
          map[x+1][y] = i;
          map = rec_finding(x_goal, y_goal, map, x+1, y, i+1, dir, tmp_path, tmp_total, not_touchable_map);
          tmp.clear();
          tmp_path.pop_back();
        } else if (is_free(x, y + 1, map, i, x, y) == true) {
          tmp.push_back(x);
          tmp.push_back(y+1);
          tmp_path.push_back(tmp);
          if (not_touchable_map[x][y+1] == 1) {
            tmp_total+=5;
          } else
            tmp_total++;
          map[x][y+1] = i;
          dir = 1;
          map = rec_finding(x_goal, y_goal, map, x, y+1, i+1, dir, tmp_path, tmp_total, not_touchable_map);
          tmp.clear();
          tmp_path.pop_back();
        } else if (is_free(x - 1, y, map, i, x, y) == true) {
          tmp.push_back(x-1);
          tmp.push_back(y);
          tmp_path.push_back(tmp);
          if (not_touchable_map[x-1][y] == 1) {
            tmp_total+=5;
          } else
            tmp_total++;
          map[x-1][y] = i;
          dir = 2;
          map = rec_finding(x_goal, y_goal, map, x-1, y, i+1, dir, tmp_path, tmp_total, not_touchable_map);
          tmp.clear();
          tmp_path.pop_back();
        } else if (is_free(x, y - 1, map, i, x, y) == true) {
          tmp.push_back(x);
          tmp.push_back(y-1);
          tmp_path.push_back(tmp);
          if (not_touchable_map[x][y-1] == 1) {
            tmp_total+=5;
          } else
            tmp_total++;
          map[x][y-1] = i;
          dir = 3;
          map = rec_finding(x_goal, y_goal, map, x, y-1, i+1, dir, tmp_path, tmp_total, not_touchable_map);
        } else {
            return(map);
        }
      case 1:
        if (is_free(x, y + 1, map, i, x, y) == true) {
          tmp.push_back(x);
          tmp.push_back(y+1);
          tmp_path.push_back(tmp);
          if (not_touchable_map[x][y+1] == 1) {
            tmp_total+=5;
          } else
            tmp_total++;
          map[x][y+1] = i;
          map = rec_finding(x_goal, y_goal, map, x, y+1, i+1, dir, tmp_path, tmp_total, not_touchable_map);
          tmp.clear();
          tmp_path.pop_back();
        } else if (is_free(x + 1, y, map, i, x, y) == true) {
          tmp.push_back(x+1);
          tmp.push_back(y);
          tmp_path.push_back(tmp);
          if (not_touchable_map[x+1][y] == 1) {
            tmp_total+=5;
          } else
            tmp_total++;
          map[x+1][y] = i;
          dir = 0;
          map = rec_finding(x_goal, y_goal, map, x+1, y, i+1, dir, tmp_path, tmp_total, not_touchable_map);
          tmp.clear();
          tmp_path.pop_back();
        } else if (is_free(x - 1, y, map, i, x, y) == true) {
          tmp.push_back(x-1);
          tmp.push_back(y);
          tmp_path.push_back(tmp);
          if (not_touchable_map[x-1][y] == 1) {
            tmp_total+=5;
          } else
            tmp_total++;
          map[x-1][y] = i;
          dir = 2;
          map = rec_finding(x_goal, y_goal, map, x-1, y, i+1, dir, tmp_path, tmp_total, not_touchable_map);
          tmp.clear();
          tmp_path.pop_back();
        } else if (is_free(x, y - 1, map, i, x, y) == true) {
          tmp.push_back(x);
          tmp.push_back(y-1);
          tmp_path.push_back(tmp);
          if (not_touchable_map[x][y-1] == 1) {
            tmp_total+=5;
          } else
            tmp_total++;
          map[x][y-1] = i;
          dir = 3;
          map = rec_finding(x_goal, y_goal, map, x, y-1, i+1, dir, tmp_path, tmp_total, not_touchable_map);
        } else {
            return(map);
        }
      case 2:
        if (is_free(x - 1, y, map, i, x, y) == true) {
          tmp.push_back(x-1);
          tmp.push_back(y);
          tmp_path.push_back(tmp);
          if (not_touchable_map[x-1][y] == 1) {
            tmp_total+=5;
          } else
            tmp_total++;
          map[x-1][y] = i;
          dir = 2;
          map = rec_finding(x_goal, y_goal, map, x-1, y, i+1, dir, tmp_path, tmp_total, not_touchable_map);
          tmp.clear();
          tmp_path.pop_back();
        } else if (is_free(x, y + 1, map, i, x, y) == true) {
          tmp.push_back(x);
          tmp.push_back(y+1);
          tmp_path.push_back(tmp);
          if (not_touchable_map[x][y+1] == 1) {
            tmp_total+=5;
          } else
            tmp_total++;
          map[x][y+1] = i;
          dir = 1;
          map = rec_finding(x_goal, y_goal, map, x, y+1, i+1, dir, tmp_path, tmp_total, not_touchable_map);
          tmp.clear();
          tmp_path.pop_back();
        } else if (is_free(x + 1, y, map, i, x, y) == true) {
          tmp.push_back(x+1);
          tmp.push_back(y);
          tmp_path.push_back(tmp);
          if (not_touchable_map[x+1][y] == 1) {
            tmp_total+=5;
          } else
            tmp_total++;
          map[x+1][y] = i;
          dir = 0;
          map = rec_finding(x_goal, y_goal, map, x+1, y, i+1, dir, tmp_path, tmp_total, not_touchable_map);
          tmp.clear();
          tmp_path.pop_back();
        } else if (is_free(x, y - 1, map, i, x, y) == true) {
          tmp.push_back(x);
          tmp.push_back(y-1);
          tmp_path.push_back(tmp);
          if (not_touchable_map[x][y-1] == 1) {
            tmp_total+=5;
          } else
            tmp_total++;
          map[x][y-1] = i;
          dir = 3;
          map = rec_finding(x_goal, y_goal, map, x, y-1, i+1, dir, tmp_path, tmp_total, not_touchable_map);
        } else {
            return(map);
        }
      case 3:
        if (is_free(x, y - 1, map, i, x, y) == true) {
          tmp.push_back(x);
          tmp.push_back(y-1);
          tmp_path.push_back(tmp);
          if (not_touchable_map[x][y-1] == 1) {
            tmp_total+=5;
          } else
            tmp_total++;
          map[x][y-1] = i;
          map = rec_finding(x_goal, y_goal, map, x, y-1, i+1, dir, tmp_path, tmp_total, not_touchable_map);
        } else if (is_free(x - 1, y, map, i, x, y) == true) {
          tmp.push_back(x-1);
          tmp.push_back(y);
          tmp_path.push_back(tmp);
          if (not_touchable_map[x-1][y] == 1) {
            tmp_total+=5;
          } else
            tmp_total++;
          map[x-1][y] = i;
          dir = 2;
          map = rec_finding(x_goal, y_goal, map, x-1, y, i+1, dir, tmp_path, tmp_total, not_touchable_map);
          tmp.clear();
          tmp_path.pop_back();
        } else if (is_free(x, y + 1, map, i, x, y) == true) {
          tmp.push_back(x);
          tmp.push_back(y+1);
          tmp_path.push_back(tmp);
          if (not_touchable_map[x][y+1] == 1) {
            tmp_total+=5;
          } else
            tmp_total++;
          map[x][y+1] = i;
          dir = 1;
          map = rec_finding(x_goal, y_goal, map, x, y+1, i+1, dir, tmp_path, tmp_total, not_touchable_map);
          tmp.clear();
          tmp_path.pop_back();
        } else if (is_free(x + 1, y, map, i, x, y) == true) {
          tmp.push_back(x+1);
          tmp.push_back(y);
          tmp_path.push_back(tmp);
          if (not_touchable_map[x+1][y] == 1) {
            tmp_total+=5;
          } else
            tmp_total++;
          map[x+1][y] = i;
          dir = 0;
          map = rec_finding(x_goal, y_goal, map, x+1, y, i+1, dir, tmp_path, tmp_total, not_touchable_map);
          tmp.clear();
          tmp_path.pop_back();
        } else {
            return(map);
        }
    }
  }
  if (tmp_total < g_total) {
    g_path = tmp_path;
    g_total = tmp_total;
  }
  return (map);
}

void set_bomb_radius(int x, int y, int value)
{

  for (int i = x-1; i != x-value-1 && i != -1; i--)
    g_map_bomb[i][y] = -1;
  for (int i = x+1; i != x+value+1 && i != 13; i++)
    g_map_bomb[i][y] = -1;
  for (int i = y-1; i != y-value-1 && i != -1; i--)
    g_map_bomb[x][i] = -1;
  for (int i = y+1; i != y+value+1 && i != 11; i++)
    g_map_bomb[x][i] = -1;
  g_map_bomb[x][y] = -1;
}

void process_map_bomb()
{
  for (int i = 0; i != 13; i++) {
    for (int j = 0; j != 11; j++) {
      if (g_map_bomb[i][j] != 0 && g_map_bomb[i][j] != -1) {
        set_bomb_radius(i, j, g_map_bomb[i][j]);
      }
    }
  }
}

int dijkstra(int x_goal, int y_goal, const std::vector<std::vector<int>> &map, int x, int y)
{
  std::vector<std::vector<int>> tmp_path;
  std::vector<int> first_pos;

  g_path.clear();
  first_pos.push_back(x);
  first_pos.push_back(y);
  tmp_path.push_back(first_pos);
//   map[0][0] = 10;
  g_total = 10000;
  std::vector<std::vector<int>> tmp = rec_finding(x_goal, y_goal, map, x, y, 11, 0, tmp_path, 0, map);
//   std::cout << g_total << std::endl;
//   for (int i = 0; i != 13; i++) {
//     for (int j = 0; j != 11; j++) {
//       std::cout << tmp[i][j] << " ";
//     }
//     std::cout << std::endl;
//   }
//   for (int i = 0; i != g_path.size(); i++) {
//     std::cout << "{" << g_path[i][0] << ";" << g_path[i][1] << "} ";
//   }
//   std::cout << std::endl;
  return (g_total);
}

int get_out(int x, int y, const std::vector<std::vector<int>> &map)
{
  if (x+1 != 13 && g_map_bomb[x+1][y] != -1 && map[x+1][y] != 1 && map[x+1][y] != 2) {
      return (2);
  } else if (x-1 != -1 && g_map_bomb[x-1][y] != -1 && map[x-1][y] != 1 && map[x-1][y] != 2) {
      return (1);
  } else if (y+1 != 11 && g_map_bomb[x][y+1] != -1 && map[x][y+1] != 1 && map[x][y+1] != 2) {
      return (4);
  } else if (y-1 != -1 && g_map_bomb[x][y-1] != -1 && map[x][y-1] != 1 && map[x][y-1] != 2) {
      return (3);
  }
  if (x+1 != 13 && map[x+1][y] != 1 && map[x+1][y] != 2)
    return (2);
  else if (x-1 != -1 && map[x-1][y] != 1 && map[x-1][y] != 2)
    return (1);
  else if (y+1 != 11 && map[x][y+1] != 1 && map[x][y+1] != 2)
    return (4);
  else if (y-1 != -1 && map[x][y-1] != 1 && map[x][y-1] != 2)
    return (3);
  return (5);
}

bool player_x_plus(const std::vector<std::vector<int>> &players, int x, int y)
{
  if ((x+1 < 13 && players[x+1][y] == 1))
    return (true);
  else if (x+2 < 13 && players[x+2][y] == 1)
    return (true);
  else if (x+3 < 13 && players[x+3][y] == 1)
    return (true);
  return (false);
}

bool player_x_minus(const std::vector<std::vector<int>> &players, int x, int y)
{
  if ((x-1 >= 0 && players[x-1][y] == 1))
    return (true);
  else if (x-2 >= 0 && players[x-2][y] == 1)
    return (true);
  else if (x-3 >= 0 && players[x-3][y] == 1)
    return (true);
  return (false);
}

bool player_y_plus(const std::vector<std::vector<int>> &players, int x, int y)
{
  if ((y+1 < 13 && players[x][y+1] == 1))
    return (true);
  else if (y+2 < 13 && players[x][y+2] == 1)
    return (true);
  else if (y+3 < 13 && players[x][y+3] == 1)
    return (true);
  return (false);
}

bool player_y_minus(const std::vector<std::vector<int>> &players, int x, int y)
{
  if ((y-1 >= 0 && players[x][y-1] == 1))
    return (true);
  else if (y-2 >= 0 && players[x][y-2] == 1)
    return (true);
  else if (y-3 >= 0 && players[x][y-3] == 1)
    return (true);
  return (false);
}

bool is_player_close(const std::vector<std::vector<int>> &players, int x, int y)
{
  if (player_x_plus(players, x, y) == true)
    return (true);
  else if (player_x_minus(players, x, y) == true)
    return (true);
  else if (player_y_plus(players, x, y) == true)
    return (true);
  else if (player_y_minus(players, x, y) == true)
    return (true);
  return (false);
}

int get_dir(int x, int y, int dest_x, int dest_y)
{
  if (dest_x > x) {
    return (2);
  } else if (dest_x < x) {
    return (1);
  } else if (dest_y > y) {
    return (4);
  } else if (dest_y < y) {
    return (3);
  } else
    return (5);
}

int bombermanIA(std::vector<std::vector<int>> map, std::vector<std::vector<int>> players, std::vector<std::vector<int>> map_bomb, int x, int y)
{
  std::vector<std::vector<int>> pos;
  std::vector<int> first;
  std::vector<int> path_lenght;
  int j = 1000000;
  g_map_bomb.clear();
  g_map_bomb = map_bomb;
  process_map_bomb();
  int tmp;
  for (int i = 0; i != 13; i++) {
    for (int k = 0; k != 11; k++) {
      if (players[i][k] == 1) {
        first.push_back(i);
        first.push_back(k);
		pos.push_back(first);
		first.clear();
      }
    }
  }
  if (pos.size() == 1)
  	return 5;
  for (int i = 0; i < pos.size(); i++) {
    if (x != pos[i][0] && y != pos[i][1]) {
      path_lenght.push_back(dijkstra(pos[i][0], pos[i][1], map, x, y));
    } else
      path_lenght.push_back(100000);
  }
  for (int i = 0; i < pos.size(); i++) {
    if (path_lenght[i] < j) {
      j = path_lenght[i];
      tmp = i;
    }
  }
  dijkstra(pos[tmp][0], pos[tmp][1], map, x, y);
  if (g_total > 500 || g_path.size() < 2) {
    return (get_out(x, y, map));
  }
  int dest_x = g_path[1][0];
  int dest_y = g_path[1][1];
//   for (int i = 0; i != 13; i++) {
//     for (int k = 0; k != 11; k++)
//       std::cout << map[i][k];
//     std::cout << std::endl;
//   }

  if (g_map_bomb[x][y] == -1 && g_map_bomb[dest_x][dest_y] != -1) {
    if (map[dest_x][dest_y] == 1)
      return (0);
    else
      return (get_dir(x, y, dest_x, dest_y));
  } else if (g_map_bomb[dest_x][dest_y] == -1 && g_map_bomb[x][y] == -1) {
    return (get_out(x, y, map));
  } else if (is_player_close(players, x, y)) {
    return (0);
  } else if (g_map_bomb[x][y] != -1 && map[dest_x][dest_y] == 1) {
      return (0);
  } else if (map[dest_x][dest_y] != -1) {
      return (get_dir(x, y, dest_x, dest_y));
  }
  return (get_dir(x, y, dest_x, dest_y));
}