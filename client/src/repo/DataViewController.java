/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package repo;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.ComboBox;
import javafx.scene.control.SingleSelectionModel;
import javafx.scene.control.Tab;

/**
 * FXML Controller class
 *
 * @author glebmillenium
 */
public class DataViewController implements Initializable {

    @FXML
    ComboBox TypeResource;
    @FXML
    ComboBox Mark;

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        TypeResource.getItems().addAll("A", "B", "C", "D", "E");
        TypeResource.getSelectionModel().select(0);
        Mark.getItems().addAll("L", "B", "C", "D", "E");
        Mark.getSelectionModel().select(0);
    }

    @FXML
    public void comboBoxTypeResourceChange() {
        System.out.println("type");
    }

    @FXML
    public void comboBoxMarkChange() {
        System.out.println("mark");
    }
}
