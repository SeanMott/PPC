/*
Power PC transcompiler || created by Sean Mott 2024+

Allows a Game Cube/Wii ROM to be converted to C++
*/

//the modes PPC can be in
enum class PPCMode
{
	Full = 0, //the default mode and will take the entire ROM and convert it to C++
	
	ASMType, //takes a ROM and generates the ASM then gives it type info but stays in ASM
};


//entry point
int main(int args, const char* argv[])
{
	//parse comments

	//lexes assembly into tokens

	return 0;
}