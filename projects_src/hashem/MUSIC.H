struct TNote
{
	int Frequency;
	int Delay;
};

class TMusic
{
private:
	TNote *Note;
public:
	void Play();
};
