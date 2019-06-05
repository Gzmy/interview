###无重复字符的最长子串 

- 使用hash映射，leftIndex保存无重复子串的左边标记，hash表中保存相同字符下一次出现时leftIndex的位置

- ```cpp
  int lengthOfLongestSubstring(std::string str) {
      int res = 0, leftIndex = 0;
      std::unordered_map<char, int> count;
      for(int i = 0; i < str.size(); ++i) {
          leftIndex = std::max(leftIndex, count[str[i]]);
          count[str[i]] = i + 1; // 随时更新下一次的地址
          res = std::max(res, i - leftIndex + 1);
      }
      return res;
  }
  ```

### 最长公共前缀

- 暂时还没思路

- ```cpp
  std::string longestCommonPrefix(std::vector<std::string>& strs) {
      std::string res;
      if(strs.empty()) {
          return res;
      }
      
      std::string tmp = strs[0];
      int maxIndex = tmp.size();
      for(int i = 1; i < strs.size(); ++i) {
          int index = 0;
          while(tmp[index] != '\0' && strs[i][index] != '\0' && tmp[index] == strs[i][index]) {
              index++;
          }
          
          if(maxIndex < index) {
              maxIndex = index;
          }
      }
      if(maxIndex == 0) {
          retunr res;
      }
      return strs[0].substr(0, maxIndex);
  }
  ```

### 字符串排列

- 使用滑动窗口解决

- ```cpp
  bool checkInclusion(std::string s1, std::string s2) {
      if(s1.empty() || s2.empty()) {
          return false;
      }
      std::vector<int> c1(26, 0);
      std::vector<int> c2(26, 0);
      
      for(char ch : s1) {
          ++c1[ch-'a'];
      }
      int size = s1.size();
      for(int i = 0; i < s2.size(); ++i) {
          if(i >= size) {
              --c2[s2[i-size]-'a'];
          }
          ++c2[s2[i]-'a'];
          if(std::equal(c1.begin(), c1.end(), c2)) {
              return true;
          }
      }
      return false;
  }
  ```

### 反转字符串中的单词

- 使用常规方法

- ```cpp
  std::string reverseWords(std::string s) {
      if(s.empty()) {
          return s;
      }
      std::string res;
      std::vector<std::string> vec;
      
      size_t start = s.find_first_not_of(' ', 0);
      while(start < s.size()) {
          std::string tmp = s.substr(start, s.find(' ', start) - start);
          vec.push_back(tmp);
          start = s.find_first_not_of(' ', s.find(' ', start));
      }
      std::reverse(vec.begin(), vec.end());
      
      size_t size = vec.size();
      for(size_t i = 0; i < size; ++i) {
          res += vec[i];
          if(i != size-1) {
              res += " ";
          }
      }
      return res;
  }
  ```



