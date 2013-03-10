

#ifndef VERTEX2_H
#define VERTEX2_H

struct VertexC
{
	VertexC(){}
	VertexC(float x, float y, float z, 
		float c1, float c2, float c3,
		float c4)
		: pos(x,y,z), color(c1,c2,c3,c4){}

	D3DXVECTOR3 pos;
	D3DXVECTOR4 color;
};

#endif // VERTEX2_H

