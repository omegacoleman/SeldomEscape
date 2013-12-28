
#include "EasyBMP.h"
#include <iostream>
#include <vector>

typedef std::pair<int, int> pixel;
typedef std::pair<pixel, pixel> rect;

bool is_empty(unsigned char r, unsigned char g, unsigned char b)
{
	return !((r == g) && (g == b));
}

std::vector<std::vector<rect> > get_char_rects(BMP& bmp)
{
    std::vector<std::vector<rect> > ret_buff;
    bool empty_line_before = true;
    bool empty_pixel_before = true;
    int y_count = 0;
	int x, y;
    for (y = 0; y < bmp.TellHeight(); y++)
	{
        bool empty_line = true;
		int x_lowerright_count = 0;
        for (x = 0; x < bmp.TellWidth(); x++)
        {  
            bool empty_pixel = true;
            if (!is_empty(bmp(x, y)->Blue, bmp(x, y)->Green, bmp(x, y)->Red))
            {
                if (empty_line_before && empty_pixel_before)
                {
                    if(empty_line)
                    {
                        ret_buff.push_back(std::vector<rect>());
                        y_count++;
                    }
                    ret_buff[y_count - 1].push_back(rect(pixel(x, y), pixel(0, 0)));
                }
                empty_line = empty_pixel = false;
			} else {
				if (!empty_pixel_before) {
					if (is_empty(bmp(x - 1, y + 1)->Blue, bmp(x - 1, y + 1)->Green, bmp(x - 1, y + 1)->Red))
					{
						ret_buff[y_count - 1][x_lowerright_count].second.first = x - 1;
						ret_buff[y_count - 1][x_lowerright_count].second.second = y;
						x_lowerright_count++;
					}
				}
			}
			empty_pixel_before = empty_pixel;
        }
        empty_line_before = empty_line;
    }
    return ret_buff;
}

void main ()
{
	BMP picture;
	picture.ReadFromFile("a.bmp");
    std::vector<std::vector<rect> > r = get_char_rects(picture);
	std::vector<std::vector<rect> >::iterator it = r.begin();
	for (; it != r.end(); it++)
	{
		std::vector<rect>::iterator itt = (*it).begin();
		for (; itt != (*it).end(); itt++)
		{
			// std::cout << "((" << itt->first.first << ", " << itt->first.second << "), (" << itt->second.first << ", " << itt->second.second << "))" << std::endl;
			std::cout << (double)itt->first.first / picture.TellWidth() << ", "
				<< 1.0 - ((double)itt->first.second / picture.TellHeight()) << ", "
				<< (double)itt->second.first / picture.TellWidth() << ", "
				<< 1.0 - ((double)itt->second.second / picture.TellHeight()) << ", "
				<< std::endl;
		}
	}
	system("PAUSE");
}