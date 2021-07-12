#pragma once
class TestPlayer{
public:
	enum class STATE {
		NONE,
		IDLE,
		WALK,
		RUN,
		ATTACK,
		DEAD
	};

private:
	STATE mState;

	void Update(void);
	void ChangeState(STATE state);
};

