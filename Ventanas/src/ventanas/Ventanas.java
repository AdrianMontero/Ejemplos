/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ventanas;

import java.awt.*;

/**
 *
 * @author adria
 */
public class Ventanas extends Frame {

    //Zona de construcción
    Button b;
    TextField txt;
    
    Ventanas(){
        this.setTitle("Mi ventana");        
        this.setSize(500, 500);
        this.setLayout(new FlowLayout(FlowLayout.LEFT));
        
        //Zona de instanciación
        b = new Button("Pulsame");
        txt = new TextField("Sin pulsar");
        txt.setSize(30, HEIGHT);
        
        
        //Zona de añadir
        this.add(b);
        this.add(txt);
        
        
        //***************************
        this.setVisible(true);
    } //Constructor
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        new Ventanas();
    }//main
   
    public boolean action(Event e, Object obj){
        if(obj.equals("Pulsame")){
            txt.setText("Pulsado");
        }
        
        return true;
    }
    
}//fin
