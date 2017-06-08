package engine;

import java.util.Comparator;
import java.io.Serializable;

public class ComparatorBytes implements Comparator<Artigo> {

    public int compare(Artigo a1, Artigo a2){
            long bytes1 = a1.getBytes();
            long bytes2 = a2.getBytes();
            long id1 = a1.getId();
            long id2 = a2.getId();

            if(bytes1 < bytes2) return 1;
            if(bytes1 > bytes2) return -1;
            else
                return Long.compare(id1,id2);
   }
}
