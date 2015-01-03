#pragma once
#include "Include.hpp"
#include "Renderer.hpp"

class RenderStage
{
public:
	RenderStage(void);
	virtual void Render() = 0;
	virtual ~RenderStage(void);
	friend bool operator <( const RenderStage &lhs, const RenderStage &rhs );
protected:
	Renderer *mRender;
private:
	uint mPriority;
	
};


bool operator<( const RenderStage &lhs, const RenderStage &rhs )
{
	return ( lhs.mPriority < rhs.mPriority );
}
