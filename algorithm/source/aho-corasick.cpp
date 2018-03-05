template< int char_size, int margin >
struct Aho_Corasick : Trie< char_size, margin > {
  static const int FAIL = char_size;
  vector< int > correct;

  Aho_Corasick() : Trie() {}

  void build(bool heavy = true) {
    correct.resize(nodes.size());
    for(int i = 0; i < nodes.size(); i++) {
      correct[i] = (int) nodes[i].accept.size();
    }

    queue< int > que;
    for(int i = 0; i <= char_size; i++) {
      if(~nodes[0].nxt[i]) {
        nodes[nodes[0].nxt[i]].nxt[FAIL] = 0;
        que.emplace(nodes[0].nxt[i]);
      } else {
        nodes[0].nxt[i] = 0;
      }
    }
    while(!que.empty()) {
      TrieNode &now = nodes[que.front()];
      correct[que.front()] += correct[now.nxt[FAIL]];
      que.pop();
      for(int i = 0; i < char_size; i++) {
        if(now.nxt[i] == -1) continue;
        int fail = now.nxt[FAIL];
        while(nodes[fail].nxt[i] == -1) fail = nodes[fail].nxt[FAIL];
        nodes[now.nxt[i]].nxt[FAIL] = nodes[fail].nxt[i];
        if(heavy) {
          auto &u = nodes[now.nxt[i]].accept;
          auto &v = nodes[nodes[fail].nxt[i]].accept;
          vector< int > accept;
          set_union(begin(u), end(u), begin(v), end(v), back_inserter(accept));
          u = accept;
        }
        que.emplace(now.nxt[i]);
      }

    }
  }

  int match(const string &str, vector< int > &result, int now = 0) {
    result.assign(size(), 0);
    int count = 0;
    for(auto &c : str) {
      while(nodes[now].nxt[c - margin] == -1) now = nodes[now].nxt[FAIL];
      now = nodes[now].nxt[c - margin];
      count += correct[now];
      for(auto &v : nodes[now].accept) ++result[v];
    }
    return (count);
  }

  int move(const char &c, int &now) {
    int count = 0;
    while(nodes[now].nxt[c - margin] == -1) now = nodes[now].nxt[FAIL];
    now = nodes[now].nxt[c - margin];
    count += correct[now];
    return (count);
  }
};
