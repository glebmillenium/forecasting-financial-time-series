/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package repo;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.geometry.Pos;
import javafx.scene.control.Label;
import javafx.scene.control.SingleSelectionModel;
import javafx.scene.layout.Pane;
import javafx.scene.control.TabPane;
import javafx.scene.control.Tab;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;

/**
 *
 * @author glebmillenium
 */
public class MainController implements Initializable {

    private ObservableList<Tab> Tabs = FXCollections.observableArrayList();
    private ConnectWithRemoteManagerSocket connect;
    @FXML
    private Label ResultConnect;

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        try {
            connect = new ConnectWithRemoteManagerSocket("127.0.0.1", 6000);
            ResultConnect.setText("ON");
        } catch (IOException ex) {
            Logger.getLogger(MainController.class.getName()).log(Level.SEVERE, null, ex);
            ResultConnect.setText("OFF");
        }
    }

    @FXML
    private Pane SpecialPane;

    @FXML
    private Tab SpecialTab;

    @FXML
    private TabPane SourceTabPane;

    @FXML
    public void specialTabPressClicked() {
        try {
            FXMLLoader loader = new FXMLLoader();
            Pane newLoadedPane = loader.load(getClass().getResource("DataView.fxml"));
            SpecialPane.getChildren().add(newLoadedPane);
            Tab tab = new Tab();
            tab.setText("Brent");
            HBox hbox = new HBox();
            hbox.getChildren().add(newLoadedPane);
            hbox.setAlignment(Pos.CENTER);
            tab.setContent(hbox);
            SourceTabPane.getTabs().add(SourceTabPane.getTabs().size() - 1, tab);
            SingleSelectionModel<Tab> selectionModel = SourceTabPane.getSelectionModel();
            selectionModel.select(tab);
            SourceTabPane.setTabClosingPolicy(TabPane.TabClosingPolicy.SELECTED_TAB);
            //DataViewController controller = loader.getController();
            //controller.setMainApp(this);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
