package engine;

import java.util.Comparator;
import java.lang.Long;


//Compara as Contribuições de dois Contribuidores
public class ComparatorContribuicoes implements Comparator<Contribuidor>{

    public int compare(Contribuidor c1, Contribuidor c2){
            int cont1 = c1.getCont();
            int cont2 = c2.getCont();
            long id1 = c1.getId();
            long id2 = c2.getId();

            if(cont1 < cont2) return 1;
            if(cont1 > cont2) return -1;
            else
                return Long.compare(id1,id2);
    }
}
