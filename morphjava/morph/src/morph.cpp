#include <cmath>
#include <vector>
#include <iostream>

#include "morph.hpp"


extern Magick::Image simage, dimage, timage;
extern std::vector<line_t> srclines, dstlines;

using namespace Magick;



float compute_u(const line_t &l, const point_t &p)
{
  point_t pq(l.p2.x - l.p1.x, l.p2.y - l.p1.y);
  point_t xp(p.x - l.p1.x, p.y - l.p1.y);
  float u = (float)(pq.x*xp.x + pq.y*xp.y)/l.length2();
  return u;
}



float compute_v(const line_t &l, const point_t &p)
{
  vec2d_t pq(l.p2 - l.p1);
  vec2d_t xp(p - l.p1);
  vec2d_t ppq= pq.perp();
  float v =  (float)(ppq.x*xp.x + ppq.y*xp.y)/l.length();
  return v;
}



point_t calc_dst_pixel(float u, float v, const line_t &l, const point_t &p)
{
  vec2d_t qp(l.p2 - l.p1);
  vec2d_t pqp = qp.perp();
  float length = l.length();
  point_t X;
  X.x = (int)(l.p1.x + u * qp.x + v * pqp.x/length);
  X.y = (int)(l.p1.y + u * qp.y + v * pqp.y/length);
  return X;
}

void morph_frame(int framenum, int totalframes)
{
  float t = (float)(framenum)/(float)(totalframes);

  std::vector<line_t> tmplines;
  for(unsigned int lnum=0; lnum < srclines.size(); lnum++)
    {
      point_t p1(((1.0-t)*srclines[lnum].p1.x + t*dstlines[lnum].p1.x), ((1.0-t)*srclines[lnum].p1.y + t*dstlines[lnum].p1.y));
      point_t p2(((1.0-t)*srclines[lnum].p2.x + t*dstlines[lnum].p2.x), ((1.0-t)*srclines[lnum].p2.y + t*dstlines[lnum].p2.y));

      line_t tline(p1,p2);
      tmplines.push_back(tline);
    }

  float a=0.5;
  float b=1.25;
  float p=1.0;

  for(int row = 0; row < 512; row++)
    for(int col = 0; col < 334; col++)
      {
	point_t temppt(col, row);
	float wsum=0;
	point_t sdsum(0,0);
	point_t ddsum(0,0);

	for(unsigned int lnum=0; lnum < srclines.size(); lnum++)
	  {
	    line_t tl(tmplines[lnum]);
	    float u = compute_u(tl, temppt);
	    float v = compute_v(tl, temppt);

	    point_t sX = calc_dst_pixel(u, v, srclines[lnum], temppt);
	    vec2d_t sDi(sX-temppt);

	    point_t dX = calc_dst_pixel(u, v, dstlines[lnum], temppt);
	    vec2d_t dDi(dX-temppt);
	    
	    
	    float dist=0.0;
	    if (u >= 1.0) 
	      {
		vec2d_t p2x(tl.p2 - temppt);
                dist = p2x.length();
	      }
	    else if(u <= 0.0)
	      {
		point_t p1x(tl.p1 - temppt);
		dist = p1x.length();
	      }
	    else
	      dist = fabs(v);
	     
	    float weight = pow((pow(tl.length(),p)/(a + dist)), b);
	    sdsum.x += sDi.x * weight;
	    sdsum.y += sDi.y * weight;
	    ddsum.x += dDi.x * weight;
	    ddsum.y += dDi.y * weight;
	    wsum += weight;
	  
	  }
	
	point_t srcpt(int(temppt.x + sdsum.x/wsum), int(temppt.y + sdsum.y/wsum));	
	point_t dstpt(int(temppt.x + ddsum.x/wsum), int(temppt.y + ddsum.y/wsum));
	
	
	Color srccolor, dstcolor;
	if ((srcpt.x >0 && srcpt.x < 334) && (srcpt.y>0 && srcpt.y < 512))
	  srccolor=simage.pixelColor(srcpt.x,srcpt.y); 
	else
	  srccolor=simage.pixelColor(col,row);
	
	if ((dstpt.x >0 && dstpt.x < 334) && (dstpt.y>0 && dstpt.y < 512))
	  dstcolor=dimage.pixelColor(dstpt.x,dstpt.y); 
	else
	  dstcolor=dimage.pixelColor(col,row);
	
	Quantum r = (1-t)*srccolor.redQuantum() + t*dstcolor.redQuantum();
	Quantum g = (1-t)*srccolor.greenQuantum() + t*dstcolor.greenQuantum();
	Quantum b = (1-t)*srccolor.blueQuantum() + t*dstcolor.blueQuantum();
	Quantum a = (1-t)*srccolor.alphaQuantum() + t*dstcolor.alphaQuantum();

	timage.pixelColor(col, row, Color(r,g,b,a));
	
      }

  std::cerr<<"Morph Complete: "<<framenum<<std::endl;
  char name[100];
  sprintf(name,"images/test_%02d.jpg",framenum);
  timage.write(name);
}

