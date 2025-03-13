#define VIDE 0xFF000000
#define HEXA 4278190080

void createObject(uint x, uint y, int masse)
{
    uint p;
    int taille = 1 + masse / 100000;

    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < taille; j++)
        {
            p = (x+i) + (y+j) * WSX;
            data_0[p] = HEXA + masse;
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
            if(data_0[p] != VIDE)
            {
                dist = sqrt((i-x)*(i-x)+(j-y)*(j-y));
                if (dist < min)
                {
                    min = dist;
                    //calcul angle theoreme Al Kashi
                    dist2 = sqrt((i-x+1)*(i-x+1)+(j-y)*(j-y));
                    dir = (((dist*dist)+1-(dist2*dist2))) / (2*dist);
                    //approximation de arcos parcequ'on ne peut pas utiliser include <math.h>
                    dir = sqrt(2-2*dir)+(sqrt(2-2*dir)*(1-dir))/11;
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
        createObject(100, 100, 100000);
        createObject(250, 350, 8000000);
	}
    // Simulation
    else
    {
        if(data_0[p] != VIDE)
        {
            double dir = dirNearestObject(x, y);
            uint dx = 0, dy = 0;
            if (dir < 45 || dir > 315) dx = 1;
            else if (dir > 135 && dir < 225) dx = -1;
            else if (dir > 225 && dir < 315) dy = 1;
            else if (dir < 135 && dir > 45) dy = -1;
        }
    }
}