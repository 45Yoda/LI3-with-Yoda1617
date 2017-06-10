package engine;


import java.lang.StringBuffer;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.UnsupportedEncodingException;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.XMLStreamReader;
import java.util.List;
import java.util.ArrayList;

public class Parser {
    public static void parseDoc(int nsnaps, ArrayList<String> args, CatArtigos artigos, CatContrib contribuidores) throws FileNotFoundException {
        String text = null;
        String[] dados = new String[10];
        int i = 0;
        int n = 0;
        long cbytes = 0;
        long cwords = 0;
        long bytes = 0;
        long words = 0;


        try{
            XMLInputFactory factory = XMLInputFactory.newInstance();

            factory.setProperty("javax.xml.stream.isCoalescing", true);

            for(;i<nsnaps;i++){
                XMLStreamReader reader = factory.createXMLStreamReader(new FileInputStream(new File(args.get(i))));


                while(reader.hasNext()){
                    int event = reader.next();

                    switch(event){
                        case XMLStreamConstants.END_DOCUMENT:
                            reader.close();
                            break;

                        case XMLStreamConstants.CHARACTERS:
                            text = reader.getText().trim();
                             try{
                                 cbytes = text.getBytes("UTF-8").length;
                             }
                             catch (UnsupportedEncodingException e){
                                 System.err.println("Erro" + e.getMessage());
                             }
                            bytes += cbytes;

                            break;

                        case XMLStreamConstants.END_ELEMENT:
                            switch(reader.getLocalName()){

                            case "text":
                                    words = countW(text);
                                    dados[6] = "" + words;
                                    words = 0;
                                    break;

                                case "title":
                                    dados[0]=text; //titulo do artigo
                                    n=0;
                                    break;

                                case "id":
                                    switch (n){
                                        case 0:
                                            dados[1]=text; //ID artigo
                                            n=1;
                                            break;
                                        case 1:
                                            dados[2]=text; //ID de Revisão
                                            n=2;
                                            break;
                                        case 2:
                                            dados[3]=text; // ID Contribuidor
                                            break;
                                    }

                                case "timestamp":
                                    dados[4]=text; // Timestamp da revisão
                                    break;

                                case "username":
                                    dados[5]=text; // Username do Contribuidor
                                    break;

                                case "revision":

                                    dados[7]="" + bytes; // Número de bytes

                                    insereDados(dados,artigos,contribuidores);
                                    words=0;
                                    bytes=0;
                                    dados[5]="";
                                    break;

                            }
                            break;
                    }
                }
            }
        }
        catch(XMLStreamException e){System.out.println("Erro");}

    }


public static int countW(String input) {
    if (input == null || input.isEmpty()) {
      return 0;
    }

    String[] words = input.split("\\s+|\n|\t");
    return words.length;
  }

private static void insereContrib(String[] dados, CatContrib contribuidores){
    if(!dados[5].isEmpty()){
        if(contribuidores.existeContribuidor(Long.parseLong(dados[3]))){
            contribuidores.getCatalogo().get(Long.parseLong(dados[3])).incrCont();
        }
        else{
            Contribuidor cont = new Contribuidor(dados[5],1,Long.parseLong(dados[3]));
            contribuidores.insereContribuidor(cont);
        }
    }
}

public static void insereDados(String[] dados, CatArtigos artigos, CatContrib contribuidores){
    if(artigos.existeArtigo(Long.parseLong(dados[1]))){
        Artigo art = artigos.getCatalogo().get(Long.parseLong(dados[1]));

        if(!art.existeRevisao(Long.parseLong(dados[2]))){
            Revisao rev = new Revisao(Long.parseLong(dados[2]),dados[4]);
            art.addRevisao(rev);
            art.incrFlag();

            insereContrib(dados,contribuidores);


            if(art.getWords()<Long.parseLong(dados[6])){
                art.setWords(Long.parseLong(dados[6]));
            }
            if(art.getBytes()<Long.parseLong(dados[7])){
                art.setBytes(Long.parseLong(dados[7]));
            }
        }
        else{
            art.incrFlag();
        }
    }
    else{
            Artigo arti = new Artigo();
            Revisao revi = new Revisao (Long.parseLong(dados[2]),dados[4]);
            arti.setTitulo(dados[0]);
            arti.setId(Long.parseLong(dados[1]));
            arti.setWords(Long.parseLong(dados[6]));
            arti.setBytes(Long.parseLong(dados[7]));
            arti.addRevisao(revi);
            arti.incrFlag();

            artigos.insereArtigo(arti);

            insereContrib(dados,contribuidores);
        }
}
}
