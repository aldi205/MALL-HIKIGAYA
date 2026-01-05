#ifndef STORES_DATA_H
#define STORES_DATA_H

// Raw data: 7 stores x 8 items each for Lantai 1 (outfit) and Lantai 2 (makanan)
struct RawItem {
    const char* name;
    const char* category;
    const char* brand;
    const char* color;
    int size;
    int price;
    int stock;
};

struct RawStore {
    const char* name;
    RawItem items[8];
};

static RawStore floor1Stores[7] = {
    { "Adidas", {
        {"Adidas T-Shirt","Baju","Adidas","Putih",0,120000,10},
        {"Adidas Hoodie","Baju","Adidas","Hitam",0,250000,5},
        {"Adidas Sneakers","Sepatu","Adidas","Putih",42,750000,7},
        {"Adidas Running","Sepatu","Adidas","Hitam",43,650000,6},
        {"Adidas Sandal A","Sandal","Adidas","Abu",40,150000,8},
        {"Adidas Sandal B","Sandal","Adidas","Navy",41,140000,9},
        {"Adidas Cap","Topi","Adidas","Hitam",0,90000,12},
        {"Adidas Socks","Aksesoris","Adidas","Putih",0,30000,20}
    } },
    { "YSL", {
        {"YSL Necklace","Perhiasan","YSL","Emas",0,1250000,3},
        {"YSL Ring","Perhiasan","YSL","Emas",0,850000,2},
        {"YSL Perfume 50ml","Parfum","YSL","",0,750000,6},
        {"YSL Perfume 100ml","Parfum","YSL","",0,1250000,4},
        {"YSL Tote Bag","Tas","YSL","Hitam",0,2000000,2},
        {"YSL Clutch","Tas","YSL","Merah",0,1650000,3},
        {"YSL Bracelet","Perhiasan","YSL","Emas",0,600000,5},
        {"YSL Keychain","Aksesoris","YSL","Emas",0,150000,10}
    } },
    { "New Balance", {
        {"NB 574","Sepatu","New Balance","Grey",42,850000,6},
        {"NB 327","Sepatu","New Balance","Black",43,900000,5},
        {"NB Running","Sepatu","New Balance","Blue",41,780000,8},
        {"NB T-Shirt","Baju","New Balance","White",0,130000,12},
        {"NB Shorts","Celana","New Balance","Black",0,160000,7},
        {"NB Cap","Topi","New Balance","Navy",0,90000,10},
        {"NB Socks","Aksesoris","New Balance","White",0,30000,20},
        {"NB Jacket","Baju","New Balance","Grey",0,420000,4}
    } },
    { "Starcros", {
        {"Starcros Tee","Baju","Starcros","Black",0,110000,15},
        {"Starcros Jeans","Celana","Starcros","Blue",32,230000,8},
        {"Starcros Sneakers","Sepatu","Starcros","White",42,650000,6},
        {"Starcros Hoodie","Baju","Starcros","Grey",0,200000,5},
        {"Starcros Belt","Aksesoris","Starcros","Black",0,80000,10},
        {"Starcros Bag","Tas","Starcros","Black",0,310000,4},
        {"Starcros Cap","Topi","Starcros","Red",0,70000,9},
        {"Starcros Sandal","Sandal","Starcros","Brown",40,120000,7}
    } },
    { "Puma", {
        {"Puma Shirt","Baju","Puma","Red",0,120000,12},
        {"Puma Shoes","Sepatu","Puma","Black",43,700000,6},
        {"Puma Sandal","Sandal","Puma","Black",41,130000,10},
        {"Puma Shorts","Celana","Puma","Grey",0,150000,8},
        {"Puma Jacket","Baju","Puma","Blue",0,400000,4},
        {"Puma Cap","Topi","Puma","Black",0,85000,11},
        {"Puma Socks","Aksesoris","Puma","White",0,30000,25},
        {"Puma Bag","Tas","Puma","Grey",0,250000,3}
    } },
    { "Levi's", {
        {"Levi's 501","Celana","Levi's","Blue",32,450000,9},
        {"Levi's 505","Celana","Levi's","Black",34,470000,7},
        {"Levi's Jacket","Baju","Levi's","Blue",0,520000,5},
        {"Levi's Shorts","Celana","Levi's","Khaki",30,210000,8},
        {"Levi's Belt","Aksesoris","Levi's","Brown",0,90000,10},
        {"Levi's Cap","Topi","Levi's","Black",0,80000,12},
        {"Levi's Shirt","Baju","Levi's","White",0,180000,6},
        {"Levi's Socks","Aksesoris","Levi's","White",0,30000,20}
    } },
    { "New Era", {
        {"New Era Cap A","Topi","New Era","Black",0,150000,20},
        {"New Era Cap B","Topi","New Era","Blue",0,160000,18},
        {"New Era Snapback","Topi","New Era","Red",0,170000,10},
        {"New Era Beanie","Topi","New Era","Grey",0,90000,14},
        {"New Era Jacket","Baju","New Era","Black",0,350000,5},
        {"New Era Shirt","Baju","New Era","White",0,140000,9},
        {"New Era Bag","Tas","New Era","Black",0,220000,6},
        {"New Era Keychain","Aksesoris","New Era","Black",0,50000,30}
    } }
};

static RawStore floor2Stores[7] = {
    { "Redog", {
        {"Nasi Goreng Special","Makanan","Redog","",0,18000,30},
        {"Nasi Goreng Telur","Makanan","Redog","",0,15000,40},
        {"Nasi Goreng Seafood","Makanan","Redog","",0,22000,20},
        {"Ayam Goreng Kremes","Makanan","Redog","",0,23000,25},
        {"Paket Hemat 2","Makanan","Redog","",0,30000,15},
        {"Es Teh","Minuman","Redog","",0,5000,50},
        {"Es Jeruk","Minuman","Redog","",0,8000,40},
        {"Kerupuk","Snack","Redog","",0,2000,100}
    } },
    { "Sushi House", {
        {"Salmon Roll","Sushi","Sushi House","",0,45000,12},
        {"Tuna Nigiri","Sushi","Sushi House","",0,30000,15},
        {"California Roll","Sushi","Sushi House","",0,40000,10},
        {"Miso Soup","Soup","Sushi House","",0,15000,25},
        {"Edamame","Snack","Sushi House","",0,12000,30},
        {"Green Tea","Minuman","Sushi House","",0,10000,40},
        {"Sushi Platter","Sushi","Sushi House","",0,120000,6},
        {"Wasabi","Condiment","Sushi House","",0,2000,50}
    } },
    { "Ramen Ichiban", {
        {"Tonkotsu Ramen","Ramen","Ramen Ichiban","",0,48000,20},
        {"Shoyu Ramen","Ramen","Ramen Ichiban","",0,42000,18},
        {"Miso Ramen","Ramen","Ramen Ichiban","",0,45000,16},
        {"Gyoza","Side","Ramen Ichiban","",0,18000,30},
        {"Chashu Extra","Topping","Ramen Ichiban","",0,15000,25},
        {"Takoyaki","Snack","Ramen Ichiban","",0,20000,22},
        {"Soft Drink","Minuman","Ramen Ichiban","",0,8000,40},
        {"Dessert Matcha","Dessert","Ramen Ichiban","",0,22000,12}
    } },
    { "Kebab Corner", {
        {"Beef Kebab","Kebab","Kebab Corner","",0,30000,25},
        {"Chicken Kebab","Kebab","Kebab Corner","",0,28000,30},
        {"Falafel Wrap","Wrap","Kebab Corner","",0,25000,20},
        {"Fries","Side","Kebab Corner","",0,12000,40},
        {"Salad Bowl","Salad","Kebab Corner","",0,20000,18},
        {"Soda","Minuman","Kebab Corner","",0,7000,50},
        {"Kebab Combo","Combo","Kebab Corner","",0,45000,15},
        {"Hot Sauce","Condiment","Kebab Corner","",0,2000,60}
    } },
    { "Burger Queen", {
        {"Classic Burger","Burger","Burger Queen","",0,35000,30},
        {"Cheese Burger","Burger","Burger Queen","",0,40000,25},
        {"Double Patty","Burger","Burger Queen","",0,60000,10},
        {"Onion Rings","Side","Burger Queen","",0,15000,40},
        {"Milkshake","Minuman","Burger Queen","",0,22000,20},
        {"Chicken Nuggets","Side","Burger Queen","",0,18000,35},
        {"Veggie Burger","Burger","Burger Queen","",0,33000,15},
        {"Fries Large","Side","Burger Queen","",0,18000,40}
    } },
    { "Pizza Express", {
        {"Margherita","Pizza","Pizza Express","",0,70000,12},
        {"Pepperoni","Pizza","Pizza Express","",0,85000,10},
        {"BBQ Chicken","Pizza","Pizza Express","",0,90000,8},
        {"Garlic Bread","Side","Pizza Express","",0,20000,25},
        {"Caesar Salad","Salad","Pizza Express","",0,30000,15},
        {"Soda","Minuman","Pizza Express","",0,8000,40},
        {"Pizza Combo","Combo","Pizza Express","",0,150000,6},
        {"Dessert Pudding","Dessert","Pizza Express","",0,18000,20}
    } },
    { "Kopi Kita", {
        {"Espresso","Kopi","Kopi Kita","",0,12000,40},
        {"Cappuccino","Kopi","Kopi Kita","",0,20000,30},
        {"Latte","Kopi","Kopi Kita","",0,22000,25},
        {"Iced Coffee","Kopi","Kopi Kita","",0,18000,35},
        {"Toast","Snack","Kopi Kita","",0,15000,20},
        {"Sandwich","Snack","Kopi Kita","",0,28000,18},
        {"Muffin","Dessert","Kopi Kita","",0,12000,22},
        {"Bottled Water","Minuman","Kopi Kita","",0,5000,60}
    } }
};

#endif // STORES_DATA_H
