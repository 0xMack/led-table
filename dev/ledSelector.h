#ifndef LEDSELECTOR_H
#define LEDSELECTOR_H


class ledSelector
{
    public:
        ledSelector();
        virtual ~ledSelector();
        void mainMenu();
    protected:
    private:
};
typedef struct {
	int ledPattern[256];
	int red;
	int green;
	int blue;
	int count;
}pattern;
#endif // LEDSELECTOR_H
