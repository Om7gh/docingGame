#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Grow and multiply your organisms to end up larger than your opponent.
 **/

typedef struct s_pos
{
    int x;
    int y;
    int parent_id;
} t_pos;

typedef struct game
{
    int width;
    int height;
    string type;
    string organ_dir;
    int owner;
    int organ_id;
    int organ_parent_id;
    int organ_root_id;
    int x;
    int y;
} game_t;

void   get_root_pos(int &x, int &y, vector<vector<game_t>> games, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (games[i][j].type == "ROOT" && games[i][j].owner == 1)
            {
                x = j;
                y = i;
                return;
            }
        }
    }
}

void get_protein_pos(int &x, int &y, vector<vector<game_t>> games, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (games[i][j].type == "BASIC")
            {
                x = j;
                y = i;
                return;
            }
        }
    }
}

int getDistance(int x1, int x2, int y1, int y2)
{
    static int i = -1;
    i++;
    return abs(x1 + i - x2) + abs(y1 - y2);
}

string getDirection(int x, int y, vector<vector<game_t>> games, int width, int height)
{
    if (y + 3 < height && games[y + 3][x].type == "BASIC")
        return ("S");
    if (y - 3 >= 0 && games[y - 3][x].type == "BASIC")
        return ("N");
    if (x + 3 < width && games[y][x + 3].type == "BASIC")
        return ("E");
    if (x - 3 >= 0 && games[y][x - 3].type == "BASIC")
        return ("W");
    return ("NONE");
}

int main()
{
    int width;  // columns in the game grid
    int height; // rows in the game grid
    int root_x = 0, root_y = 0;
    int protein_x, protein_y;
    static int v = 1;
    cin >> width >> height;
    cin.ignore();
    vector<vector<game_t>> games(height, vector<game_t>(width));
    vector<t_pos> organ_pos;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            games[i][j].y = i;
            games[i][j].x = j;
            games[i][j].type = "NONE";
        }
    }

    while (1)
    {
        int entity_count;
        cin >> entity_count;
        cin.ignore();
        for (int i = 0; i < entity_count; i++)
        {
            int x, y;
            string type;
            int owner, organ_id, organ_parent_id, organ_root_id;
            string organ_dir;
            cin >> x >> y >> type >> owner >> organ_id >> organ_dir >> organ_parent_id >> organ_root_id;
            cin.ignore();

            // Update the grid cell
            games[y][x].type = type;
            games[y][x].owner = owner;
            games[y][x].organ_id = organ_id;
            games[y][x].organ_dir = organ_dir;
            games[y][x].organ_parent_id = organ_parent_id;
            games[y][x].organ_root_id = organ_root_id;
        }
        // Protein stocks
        int my_a, my_b, my_c, my_d;
        cin >> my_a >> my_b >> my_c >> my_d;
        cin.ignore();
        int opp_a, opp_b, opp_c, opp_d;
        cin >> opp_a >> opp_b >> opp_c >> opp_d;
        cin.ignore();

        // Number of required actions
        int required_actions_count;
        cin >> required_actions_count;
        cin.ignore();
        for (int i = 0; i < required_actions_count; i++)
        {
            get_root_pos(root_x, root_y, games, width, height);
            get_protein_pos(protein_x, protein_y, games, width, height);
            for (int j = root_y; j < height; j++)
            {
                for (int k = root_x; k < width; k++)
                {
                    if (games[j][k].type != "NONE") continue;
                    int dis = getDistance(root_x, protein_x, root_y, protein_y);
                    if (dis > 2)
                    {
                        cout << "GROW 1 " << k + v << " " << j << " BASIC" << endl;
                        games[j][k].type = "BASIC";
                        goto next;
                    }
                    else
                    {
                        string dir = getDirection(k, j, games, width, height);
                        cout << "GROW 1 " << k + v << " " << j << " HARVESTER " << dir << endl;
                        games[j][k].type = "HARVESTER";
                        goto next;
                    }
                }
            }
            v++;
            next: ;
        }
    }
}
