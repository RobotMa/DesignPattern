
class ClothesVisualizer
{
public:
    ~ClothesVisualizer() = default;

    virtual void printClothesInfo() const      = 0;
    virtual void displayClothesPicture() const = 0;
};