/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package repo;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.geometry.Pos;
import javafx.scene.control.Label;
import javafx.scene.control.SingleSelectionModel;
import javafx.scene.layout.Pane;
import javafx.scene.control.TabPane;
import javafx.scene.control.Tab;
import javafx.scene.layout.HBox;

/**
 *
 * @author glebmillenium
 */
public class MainController implements Initializable {

    @FXML
    private Tab SpecialTab;
    public static ConnectWithRemoteManagerSocket connect;
    @FXML
    private Label ResultConnect;
    @FXML
    private Pane SpecialPane;

    @FXML
    public TabPane SourceTabPane;

    @Override
    public void initialize(URL url, ResourceBundle rb) {
        try {
            connect = new ConnectWithRemoteManagerSocket("127.0.0.1", 6000);
            ResultConnect.setText("ON");
        } catch (IOException ex) {
            ResultConnect.setText("OFF");
        }

        SpecialTab.setOnSelectionChanged(new EventHandler<Event>() {
            @Override
            public void handle(Event t) {
                specialTabPressClicked();
            }
        });
        specialTabPressClicked();
    }

    @FXML
    public void specialTabPressClicked() {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("DataView.fxml"));

            Tab tab = new Tab();

            Pane newLoadedPane = (Pane) loader.load();
            

            SpecialPane.getChildren()
                    .add(newLoadedPane);
            HBox hbox = new HBox();
            hbox.getChildren()
                    .add(newLoadedPane);
            hbox.setAlignment(Pos.CENTER);
            tab.setContent(hbox);
            SourceTabPane.getTabs()
                    .add(SourceTabPane.getTabs().size() - 1, tab);
            SingleSelectionModel<Tab> selectionModel = SourceTabPane.getSelectionModel();
            selectionModel.select(tab);

            SourceTabPane.setTabClosingPolicy(TabPane.TabClosingPolicy.SELECTED_TAB);
            DataViewController controller = loader.<DataViewController>getController();
            controller.setTab(tab);
        } catch (IOException e) {

        }
    }
}
