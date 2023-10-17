#ifndef STRINGMULTIPLY
#define STRINGMULTIPLY
#include <iostream>
#include <string>
//#include <cstdlib>
std::string multiply(const std::string &vl1, const std::string &vl2)
{
        auto sum
        {
                [](const std::string &vl1, const std::string &vl2)
                {
                        std::string minNum = "";
                        std::string imin = "";
                        std::string imax = "";
                        std::string res = "";
                        int firstNum = 0;
                        int secondNum = 0;
                        int actNum = 0;
                        if(vl1.size() >= vl2.size())
                        {
                                imax = vl1;
                                imin = vl2;
                        }
                        else
                        {
                                imax = vl2;
                                imin = vl1;
                        }
                        for(int i = 0; i < imax.size() - imin.size(); ++i)      minNum.push_back('0');
                        minNum += imin;
//      std::cout << imax << ", " << minNum << std::endl;
                        for(int i = 0; i < imax.size(); ++i)
                        {
				if(imax[i] != '0')
				{
                                        firstNum = i;
                                        break;
				}
			}
                        for(int i = 0; i < minNum.size(); ++i)
			{
                                if(minNum[i] != '0')
                                {
                                        secondNum = i;
                                        break;
                                }
                                secondNum = i;
                        }
                        actNum = (firstNum <= secondNum) ? firstNum : secondNum;
//      std::cout << firstNum << ", " << secondNum << std::endl;
//      std::cout << "act: " << actNum << std::endl;
//      std::cout << imax << " + " << minNum << " = ";
                        int resI(0), bufI(0);
                        for(int i = imax.size() - 1; i >= 0; --i)
                        {
                                resI = bufI + imax[i] + minNum[i] - 96;
                                bufI = resI / 10;
                                resI %= 10;
                                if(i >= actNum) res.insert(0, 1, resI + 48);
                                resI = 0;
                                if(i == 0 && bufI != 0)
                                {
//                      const char insBuf = bufI + 48;
                                	res.insert(0, 1, bufI + 48);
				}//std::cout << res << std::endl;
			}
                        return res;
                }
        };
        std::string imin = "";
        std::string imax = "";
        std::string res = "";
        if(vl1.size() >= vl2.size())
        {
                imax = vl1;
                imin = vl2;
        }
        else
        {
                imax = vl2;
                imin = vl1;
        }
        int resI(0), buf(0);
        std::string bufS{""};
        for(int i = imin.size() - 1; i >= 0; --i)
        {
                for(int j = imax.size() - 1; j >= 0; --j)
                {
                        resI = (imax[j] - 48) * (imin[i] - 48);// + buf;
//                      std::cout << resI << std::endl;
//                      resI %= 10;
//                      buf = resI / 10;
//                      resI %= 10;
                        bufS = std::to_string(resI);
//                      std::cout << resI << ",";
                        for(int k = 0; k < (int(imax.size() - 1 - j) + int(imin.size() - 1 - i)); ++k)
                        {
                                bufS.push_back('0');
//                              std::cout << "0";
                        }
                        bufS = sum(bufS, std::to_string(buf));
//                      std::cout << std::endl;
                        res = sum(res, bufS);
//                      std::cout << " " <<bufS << std::endl;
                        if(i == 0 && j == 0 && buf != 0)
                        {
//                              const char insBuf = buf + 48;
                                res.insert(0, 1, buf + 48);
                        }
                }
        }
        return res;
}


#endif

