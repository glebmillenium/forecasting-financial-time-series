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
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.MapValueFactory;
import static repo.MainController.connect;

/**
 * FXML Controller class
 *
 * @author glebmillenium
 */
public class DataViewController implements Initializable {

    private static DataInputStream in;
    private static DataOutputStream out;
    private String lastDate;
    private String lastValue;
    private XYChart.Series series;
    private XYChart.Series forecastSeries;
    @FXML
    TableView table;
    @FXML
    ComboBox TypeResource;
    @FXML
    ComboBox Mark;
    @FXML
    LineChart<String, Number> dataLineChart;
    @FXML
    private Tab tab;
    private boolean change = false;
    List<Integer> listIdMark;
    List<Integer> listIdTypeResource;

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        listIdMark = new ArrayList<Integer>();
        listIdTypeResource = new ArrayList<Integer>();

        setConnectAndData(connect.getDataInputStream(),
                connect.getDataOutputStream());
    }

    @FXML
    public void comboBoxTypeResourceChange() {
        setMark();
    }

    @FXML
    public void comboBoxMarkChange() {
        if (accessChange) {
            setGraphData();
            setForecast();
        }
    }

    @FXML
    public void setConnectAndData(DataInputStream dataInputStream,
            DataOutputStream dataOutputStream) {
        in = dataInputStream;
        out = dataOutputStream;
        setBeginData();
    }

    public void setTab(Tab ltab)
    {
        this.tab = ltab;
        this.tab.setText(Mark.getSelectionModel().getSelectedItem().toString());
        change = true;
    }
    
    private void setBeginData() {
        
        series = new XYChart.Series();
        forecastSeries = new XYChart.Series();
        dataLineChart.getData().add(series);
        dataLineChart.getData().add(forecastSeries);
        setResources();
        setMark();
        setGraphData();
        setForecast();
    }

    void setForecast() {
        try {

            String result = "";
            int index = Mark.getSelectionModel().getSelectedIndex();
            int id_data_resources = listIdMark.get(index);
            result = ConnectWithRemoteManagerSocket.sendMessage(
                    "--get_forecast " + id_data_resources, in, out, 1048576);
            forecastSeries.getData().clear();
            forecastSeries.setName("прогнозируемые данные");
            ObservableList<XYChart.Data> datas = FXCollections.observableArrayList();
            
            if (result.length() > 3) {
                datas.add(new XYChart.Data(lastDate,
                        Float.parseFloat(lastValue)));
                String[] date = lastDate.split("-");
                double cyear = Double.parseDouble(date[0]);
                double cmonth = Double.parseDouble(date[1]);
                double cday = Double.parseDouble(date[2]);
                float v = (float) (cyear * 100 + (100
                        * (30.4 * cmonth + cday) / 366.0001));
                String[] firstScale = result.split("\\|\\|");
                ObservableList<Map> allData = table.getItems();
                for (int i = firstScale.length - 1; i >= 0; i--) {
                    Map<String, String> dataRow = new HashMap<>();
                    v++;
                    int year = (int) (v / 100.0);
                    double path = (double) ((v - year * 100.0));
                    int month = (int) (path / (366.00001 / 30.4));
                    int day = (int) Math.round(path * 366.0001 / 100.0 % 30.04);
                    if (day == 0) {
                        day++;
                    }
                    month++;

                    String sday = day < 10 ? "0" + day : String.valueOf(day);
                    String smonth = month < 10 ? "0" + month : String.valueOf(month);
                    String graphdate = year + "-" + smonth + "-" + sday;
                    datas.add(new XYChart.Data(graphdate,
                            Float.parseFloat(firstScale[i])));
                    
                    dataRow.put(head[0], graphdate + "-П");
                    String str = String.format("%.2f", Float.parseFloat(firstScale[i]));
                    dataRow.put(head[1], str);
                    allData.add(dataRow);
                }
                
                forecastSeries.setData(datas);
            }
        } catch (IOException ex) {
            Logger.getLogger(DataViewController.class.getName()).log(Level.SEVERE, null, ex);
        } catch (InterruptedException ex) {
            Logger.getLogger(DataViewController.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    String[] head;
    private void addColumn(TableView table, String[] head) {
        for (int i = 0; i < head.length; i++) {
            TableColumn<Map, String> column = new TableColumn<>(head[i]);
            column.setCellValueFactory(new MapValueFactory(head[i]));
            column.setMinWidth(120);
            table.getColumns().add(column);
        }
    }

    private void setGraphData() {
        try {
            series.getData().clear();
            table.getColumns().clear();
            table.getItems().clear();
            String result = "";
            int index = Mark.getSelectionModel().getSelectedIndex();
            int id_data_resources = listIdMark.get(index);
            result = ConnectWithRemoteManagerSocket.sendMessage(
                    "--get_data " + id_data_resources, in, out, 1048576);

            String[] firstScale = result.split("\\|\\|");
            head = firstScale[0].split(",");
            addColumn(table, head);

            ObservableList<Map> allData = table.getItems();

            dataLineChart.setTitle(
                    Mark.getSelectionModel().getSelectedItem().toString());

            if(change) 
            {
                this.tab.setText(
                        Mark.getSelectionModel().getSelectedItem().toString());
            }
            
            series.setName("реальные данные");
            ObservableList<XYChart.Data> datas = FXCollections.observableArrayList();
            float min = Float.MAX_VALUE;
            float max = Float.MIN_VALUE;
            lastValue = firstScale[1].split(",")[1];
            lastDate = firstScale[1].split(",")[0];
            for (int i = firstScale.length - 1; i >= 1; i--) {
                Map<String, String> dataRow = new HashMap<>();
                String[] secondScale = firstScale[i].split(",");
                for (int j = 0; j < table.getColumns().size(); j++) {
                    String mapKey = head[j];
                    String value = secondScale[j];
                    dataRow.put(mapKey, value);
                }
                if (Float.parseFloat(secondScale[1]) < min) {
                    min = Float.parseFloat(secondScale[1]);
                }
                if (Float.parseFloat(secondScale[1]) > max) {
                    max = Float.parseFloat(secondScale[1]);
                }
                datas.add(new XYChart.Data(secondScale[0],
                        Float.parseFloat(secondScale[1])));
                allData.add(dataRow);
            }

            series.setData(datas);
            NumberAxis axis = (NumberAxis) dataLineChart.getYAxis();
            axis.setAutoRanging(false);
            axis.setLowerBound(min * 0.95);
            axis.setUpperBound(max * 1.05);
        } catch (IOException ex) {
        } catch (InterruptedException ex) {
        }
    }

    boolean accessChange = false;

    @FXML
    private void setMark() {
        try {
            String result;
            int index = TypeResource.getSelectionModel().getSelectedIndex();
            int id_type_resources = listIdTypeResource.get(index);
            result = ConnectWithRemoteManagerSocket.sendMessage(
                    "--get_marks " + id_type_resources, in, out, 1024);
            accessChange = false;
            Mark.getItems().clear();
            accessChange = true;
            listIdMark.clear();
            String[] firstScale = result.split("\\|\\|");
            for (int i = 0; i < firstScale.length; i++) {
                String[] secondScale = firstScale[i].split(",");
                listIdMark.add(Integer.parseInt(secondScale[0]));
                Mark.getItems().add(secondScale[1]);
            }
            Mark.getSelectionModel().select(0);
        } catch (IOException ex) {
            Logger.getLogger(DataViewController.class.getName()).log(Level.SEVERE, null, ex);
        } catch (InterruptedException ex) {
            Logger.getLogger(DataViewController.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void setResources() {
        try {

            String result = "";
            result = ConnectWithRemoteManagerSocket.sendMessage(
                    "--get_types", in, out, 1024);
            String[] firstScale = result.split("\\|\\|");

            TypeResource.getItems().clear();
            listIdTypeResource.clear();
            for (int i = 0; i < firstScale.length; i++) {
                String[] secondScale = firstScale[i].split(",");
                listIdTypeResource.add(Integer.parseInt(secondScale[0]));
                TypeResource.getItems().add(secondScale[1]);
            }
            TypeResource.getSelectionModel().select(0);
        } catch (IOException ex) {
            Logger.getLogger(DataViewController.class.getName()).log(Level.SEVERE, null, ex);
        } catch (InterruptedException ex) {
            Logger.getLogger(DataViewController.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
