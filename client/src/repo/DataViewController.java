/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package repo;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.chart.XYChart.Data;
import javafx.scene.control.ComboBox;
import static repo.MainController.connect;

/**
 * FXML Controller class
 *
 * @author glebmillenium
 */
public class DataViewController implements Initializable {

    private static DataInputStream in;
    private static DataOutputStream out;
    
    @FXML
    ComboBox TypeResource;
    @FXML
    ComboBox Mark;
    @FXML
    LineChart<Number, Number> dataLineChart;
    @FXML
    CategoryAxis xAxis;
    @FXML
    NumberAxis yAxis;
    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        TypeResource.getItems().addAll("A", "B", "C", "D", "E");
        TypeResource.getSelectionModel().select(0);
        Mark.getItems().addAll("L", "B", "C", "D", "E");
        Mark.getSelectionModel().select(0);
        
//        NumberAxis x = new NumberAxis();
//        NumberAxis y = new NumberAxis();
//        dataLineChart = new LineChart<Number, Number>(x,y);
        dataLineChart.setTitle("Series");
        XYChart.Series series1 = new XYChart.Series();
        XYChart.Series series2 = new XYChart.Series();
        series2.setName("cos(x)");
        series1.setName("sin(x)");
        ObservableList<XYChart.Data> datas = FXCollections.observableArrayList();
        ObservableList<XYChart.Data> datas2 = FXCollections.observableArrayList();
        for(int i=0; i<20; i++){
            datas.add(new XYChart.Data("a"+6*i, Math.sin(i)));
            datas2.add(new Data("a"+i, Math.cos(i)));
        }

        series1.setData(datas);
        series2.setData(datas2);

        dataLineChart.getData().add(series1);
        dataLineChart.getData().add(series2);
        
        setConnectAndData(connect.getDataInputStream(), 
                    connect.getDataOutputStream());
    }

    @FXML
    public void comboBoxTypeResourceChange() {
        System.out.println("type");
    }

    @FXML
    public void comboBoxMarkChange() {
        System.out.println("mark");
    }
    
    @FXML
    public void setConnectAndData(DataInputStream dataInputStream, 
            DataOutputStream dataOutputStream)
    {
        in = dataInputStream;
        out = dataOutputStream;
        setBeginData();
    }
    
    private void setBeginData()
    {
        try {
            String result;
            int id_type_resources = 0;
            int id_data_resources = 0;
            result = ConnectWithRemoteManagerSocket.sendMessage(
                    "--get_types", in, out, 1024);
            System.out.println(result);
            result = ConnectWithRemoteManagerSocket.sendMessage(
                    "--get_marks " +id_type_resources, in, out, 1024);
            result = ConnectWithRemoteManagerSocket.sendMessage(
                    "--get_data " + id_data_resources, in, out, 1048576); // 1mb
            System.out.println("init in and out");
        } catch (IOException ex) {
            
        } catch (InterruptedException ex) {
            
        }
    }
}
