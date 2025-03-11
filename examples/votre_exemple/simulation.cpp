#include <math.h>

#define VIDE 0xFF000000
#define OBJ 0xFFFFFFFF

void createObject(uint x, uint y, int masse)
{
    uint p;

    for (int i = 0; i < masse; i++)
    {
        for (int j = 0; j < masse; j++)
        {
            p = (x+i) + (y+j) * WSX;
            data_0[p] = OBJ;
        }
    }
}

double dirNearestObject(uint x, uint y)
{
    double dist, dist2;
    double min = WSX + WSY;
    double dir = 0;
    uint p;

    for (int i = 0; i < WSX; i++)
    {
        for (int j = 0; j < WSY; j++)
        {
            p = x + y * WSX;
            if(data_0[p] == OBJ)
            {
                dist = sqrt((i-x)*(i-x)+(j-y)*(j-y));
                if (dist < min)
                {
                    min = dist;
                    //calcul angle theoreme Al Kashi
                    dist2 = sqrt((i-x+1)*(i-x+1)+(j-y)*(j-y));
                    dir = (((dist*dist)+1-(dist2*dist2))) / (2*dist)
                    dir = acos(dir);
                }
            }
        }
    }

    return dir;
}

void main()
{
    uint x = gl_GlobalInvocationID.x;
	uint y = gl_GlobalInvocationID.y;
    uint p = x + y * WSX;

    // Initialisation
	if (step == 0)
	{
		data_0[p] = VIDE;
        createObject(100, 100, 10);
        createObject(250, 350, 20);
	}
    // Simulation
    else
    {
        if(data_0[p] == OBJ)
        {
            double dir = dirNearestObject(x, y);
            uint dx, dy;
            if (dir < 45 || dir > 315) dx = 1;
            else if (dir > 135 && dir < 225) dx = -1;
            //TODO
        }
    }
}