/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package repo;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.control.Label;
import javafx.scene.layout.Pane;
import javafx.scene.layout.AnchorPane;

/**
 *
 * @author glebmillenium
 */
public class MainController implements Initializable {

    //private ObservableList<Person> personData = FXCollections.observableArrayList();
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
    }

    @FXML
    Pane panel;

    @FXML
    public void tabPressClicked() {
        try {
            // Загружаем сведения об адресатах.
            Pane newLoadedPane = FXMLLoader.load(getClass().getResource("DataView.fxml"));
            panel.getChildren().add(newLoadedPane);
            // Даём контроллеру доступ к главному приложению.
            //DataViewController controller = loader.getController();
            //controller.setMainApp(this);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
