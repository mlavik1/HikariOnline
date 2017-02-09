#ifndef HIKARI_TICKABLE_H
#define HIKARI_TICKABLE_H

namespace Hikari
{
	enum class TickGroup
	{
		Invalid,
		Actors,
		Components
	};

	class TickProperties
	{
	public:
		bool mActive = false;
		float mTickInterval = 0.0f;
	};

	class Tickable
	{
	protected:
		TickProperties mTickProperties;
	public:
		virtual void Tick(float arg_deltatime) = 0;
		virtual void Activate() = 0;
		virtual void Deactivate() = 0;

		// todo....
		//   should maybe use a TickFunction like UE instead?
	};
}

#endif
