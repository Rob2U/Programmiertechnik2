#include <array>
#include <iostream>
#include <tuple>
#include <vector>

class TowerOfHanoi
{
public:
    using Tower = std::pair<char, std::vector<int>>;

    explicit TowerOfHanoi(int item_count)
            : item_count(item_count)
    {
        for (int i = item_count; i > 0; --i)
        {
            towers[0].second.emplace_back(i);
        }
    }

    void runSimulation()
    {
        print();
        std::ignore = getchar();
        simulateNextStep(item_count, towers[0], towers[1], towers[2]);
        std::cout << "Minimal number of moves: " << moves << std::endl;

        std::ignore = getchar();
    }

private:
    void simulateNextStep(const int n, Tower& a, Tower& b, Tower& c)
    {
        // move n plates from a over b to c
        // TODO 5.2: Implement ToH and print

        if(n == 1){
            //wait for key push
            moves++;

            // move disc from a directly to c (no auxiliary stack required)
            c.second.push_back(a.second[a.second.size()-1]);
            a.second.pop_back();

            //print new view
            print();
            std::cin.get();
        }
        else{
            simulateNextStep(n-1, a, c, b); // move n-1 stack of a to stack b
            simulateNextStep(1, a, b, c); // move remaining disc of a to c
            simulateNextStep(n-1, b, a, c); // move n-1 stack b to stack c
        }

    }
    std::string generatelinefortower(int tower, int line){
        std::string line_a = "";
        //calculate basic construction

        //calculate string for stack a
		line = 8 - line;
        int size_a = towers[tower].second.size();
        if (size_a <= line) {
            for (int j = 0; j < 20; j++) {
                line_a += (j%20==10) ? "|" : " ";
            }
        }
        else {
            for (int j = 0; j < 20; j++) {
                if (j > 20/2 + towers[tower].second.at(line) ||  j  < 20/2 - towers[tower].second.at(line)) {
                    line_a += " ";
                }
                else {
                    line_a += "#";
                }
            }
        }
        return line_a;
    }

    void print()
    {
#ifdef _WIN32
        std::system("cls");
#else
        std::system("clear");
#endif

        // TODO 5.2: Print current state

        // make ascii graphics
#ifdef _WIN32
        std::system("cls");
#else
        std::system("clear");
#endif
        for (int i = 0; i <= 8; i++){

            std::string line_a = "";
            //calculate basic construction

            //calculate string for stack a
            std::string line = generatelinefortower(0, i);
            line += " " + generatelinefortower(1, i);
            line += " " + generatelinefortower(2, i);
            std::cout << line << std::endl;
			

            std::string placeholder = "";
			for (int i = 0; i < 63; i++){
				placeholder += (i%21==10) ? "|" : " ";
			}
			std::cout << placeholder << std::endl;
        }
		std::string base = "";
		for (int i = 0; i < 62; i++){
			base += (i%21==0) ? " " : "_";
		}
        std::cout << base << std::endl << base << std::endl;
		base = "";
		for (int i = 0; i < 62; i++){
			base += (i%21==10) ? std::string({char(i/21 + 65)})  : ((i%21==0) ? " " : "_");
		}
		std::cout << base << std::endl;
    }

    std::array<Tower, 3> towers{ Tower('A', {}), Tower('B', {}), Tower('C', {}) };

    int item_count;
    unsigned int moves = 0;
};

int main()
{
    constexpr int ItemCount = 8;
    TowerOfHanoi toh(ItemCount);
    toh.runSimulation();

    return 0;
}
