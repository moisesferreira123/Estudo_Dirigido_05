#include <memory>
#include <vector>

// Interface
class SearchStrategy {
  public:
    virtual int search(int productCodes[], int size, int key) const = 0;
    virtual ~SearchStrategy() = default;
};
// ---

// Classes concretas
class LinearSearchStrategy : public SearchStrategy {
  int search(int productCodes[], int size, int key) const override{
    for(int i{0};i<size;i++){
      // Produto encontrado.
      if(productCodes[i] == key) return i;
    }
    // Produto não encontrado.
    return -1;
  }
};

class BinarySearchStrategy : public SearchStrategy {
  int search(int productCodes[], int size, int key) const override{
    int begin = 0;
    int end = size;
    while(begin<end){
      int mid = (end-begin)/2 + begin;
      if(productCodes[mid] == key){
        // Produto encontrado.
        return mid;
      }else if(productCodes[mid] < key){
        begin = mid+1;
      }else{
        end = mid;
      }
    }
    // Produto não encontrado.
    return -1;
  }
};
// ---

// Classe de contexto
class InventorySearchContext {
  private:
    std::unique_ptr<SearchStrategy> strategy;
  public:
    explicit InventorySearchContext(std::unique_ptr<SearchStrategy> strategy) : strategy(std::move(strategy)) {}

    void setStrategy(std::unique_ptr<SearchStrategy> desiredStrategy) {
      strategy = std::move(desiredStrategy);
    }

    int performSearch(int productCodes[], int size, int key){
      return strategy->search(productCodes, size, key);
    }
};
// ---