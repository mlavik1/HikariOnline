#ifndef HIKARI_TICKABLE_H
#define HIKARI_TICKABLE_H

namespace Hikari
{
	class Tickable
	{
	protected:
		bool mActive = false;
		float mTickInterval = 0.0f;
	public:
		virtual void Tick(float arg_deltatime) = 0;

		// todo....
		//   should maybe use a TickFunction like UE instead?
	};
}

#endif
