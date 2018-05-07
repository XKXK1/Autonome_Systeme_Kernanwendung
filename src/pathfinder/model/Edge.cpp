//
// Created by Grages, Philip on 07.05.18.
//

class Edge {
    private:
    final int id_one;
    final int id_two;
    final float weight;

    public:
    void Edge(int id_one, int id_two, float weight){
        this.id_one = id_one;
        this.id_two = id_two;
        this.weight = wight;
    }

    int getIdOne(){return id_one;}
    int getIdTwo(){return id_two;}
    float getWeight(){return weight;}

};