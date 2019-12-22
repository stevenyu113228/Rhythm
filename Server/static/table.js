function get_table(type){
    if(type=="soft"){
        return "<table style='left:5%; position:relative; width:90%; text-align: center; font-size:14px; '> \
        <tr style= 'border-bottom: 1px solid;'>\
            <td width = '150' height = '50'>Music name</td>\
            <td width = '100' height = '50'>Author name</td>\
            <td width = '100' height = '50'></td>\
        </tr>\
        <tr style='border-bottom: 1px solid;'>\
            <td width = '150' height = '50'><p style='line-height:40px; text-align: left; margin:0 0 0 0; padding-left:20px;'>  Bobby Drake</p></td>\
            <td>BenJamin Banger</td>\
            <!-- <td>2:43</td> -->\
            <!-- <td><div style='width:100%; height:100%;'><input type='button' value='' class='play_button' style='background-color:transparent; border:0px;'></td> -->\
            <!-- <td><input type='checkbox' checked data-toggle='toggle' data-on='<i class='fa fa-play'></i>' data-off='<i class='fa fa-pause'></i>'></td> -->\
            <td>\
                <div style='width:100%; height:100%;'>\
                    <audio src='./static/soft_music/BenJamin_Banger_-_01_-_Bobby_Drake.mp3' style='height:30px; margin-top:5px; padding:0px;' controls>\
                        <h3>遇到不支援的瀏覽器會出現這行字</h3>\
                    </audio>\
                </div>\
            </td>\
        </tr>\
        <tr style='border-bottom: 1px solid;'>\
            <td width = '150' height = '45'><p style='line-height:40px; text-align: left; margin:0 0 0 0; padding-left:20px;'>  Kiss And Tell breezy bossa nova</p></td>\
            <td>Keshco</td>\
            <td>\
                <div style='width:100%; height:100%;'>\
                    <audio src='./static/soft_music/Keshco_-_18_-_Kiss_And_Tell_breezy_bossa_nova.mp3' style='height:30px; margin-top:5px; padding:0px;' controls>\
                        <h3>遇到不支援的瀏覽器會出現這行字</h3>\
                    </audio>\
                </div>\
            </td>\
        </tr>\
        <tr style='border-bottom: 1px solid;'>\
            <td width = '150' height = '45'><p style='line-height:40px; text-align: left; margin:0 0 0 0; padding-left:20px;'>  Starling</p></td>\
            <td>Podington Bear</td>\
            <td>\
                <div style='width:100%; height:100%;'>\
                    <audio src='./static/soft_music/Podington_Bear_-_Starling.mp3' style='height:30px; margin-top:5px; padding:0px;' controls>\
                        <h3>遇到不支援的瀏覽器會出現這行字</h3>\
                    </audio>\
                </div>\
            </td>\
        </tr>\
        <tr style='border-bottom: 1px solid;'>\
            <td width = '150' height = '45'><p style='line-height:40px; text-align: left; margin:0 0 0 0; padding-left:20px;'>  Dusk Cathedral</p></td>\
            <td>S Lee Rosevere</td>\
            <td>\
                <div style='width:100%; height:100%;'>\
                    <audio src='./static/soft_music/S_Lee_Rosevere_-_03_-_Dusk_Cathedral.mp3' style='height:30px; margin-top:5px; padding:0px;' controls>\
                        <h3>遇到不支援的瀏覽器會出現這行字</h3>\
                    </audio>\
                </div>\
            </td>\
            </tr>\
    </table>\
    "
    }
    else if(type == "hard"){
        return "<table style='left:5%; position:relative; width:90%; text-align: center; font-size:14px; '> \
        <tr style= 'border-bottom: 1px solid;'>\
            <td width = '150' height = '50'>Music name</td>\
            <td width = '100' height = '50'>Author name</td>\
            <td width = '100' height = '50'></td>\
        </tr>\
        <tr style='border-bottom: 1px solid;'>\
            <td width = '150' height = '50'><p style='line-height:40px; text-align: left; margin:0 0 0 0; padding-left:20px;'>  Run Come</p></td>\
            <td>Shaolin Dub</td>\
            <!-- <td>2:43</td> -->\
            <!-- <td><div style='width:100%; height:100%;'><input type='button' value='' class='play_button' style='background-color:transparent; border:0px;'></td> -->\
            <!-- <td><input type='checkbox' checked data-toggle='toggle' data-on='<i class='fa fa-play'></i>' data-off='<i class='fa fa-pause'></i>'></td> -->\
            <td>\
                <div style='width:100%; height:100%;'>\
                    <audio src='./static/hard_music/Shaolin_Dub_-_01_-_Run_Come.mp3' style='height:30px; margin-top:5px; padding:0px;' controls>\
                        <h3>遇到不支援的瀏覽器會出現這行字</h3>\
                    </audio>\
                </div>\
            </td>\
        </tr>\
        <tr style='border-bottom: 1px solid;'>\
            <td width = '150' height = '45'><p style='line-height:40px; text-align: left; margin:0 0 0 0; padding-left:20px;'>  Pied Piper</p></td>\
            <td>Shaolin Dub</td>\
            <td>\
                <div style='width:100%; height:100%;'>\
                    <audio src='./static/hard_music/Shaolin_Dub_-_06_-_Pied_Piper.mp3' style='height:30px; margin-top:5px; padding:0px;' controls>\
                        <h3>遇到不支援的瀏覽器會出現這行字</h3>\
                    </audio>\
                </div>\
            </td>\
        </tr>\
        <tr style='border-bottom: 1px solid;'>\
            <td width = '150' height = '45'><p style='line-height:40px; text-align: left; margin:0 0 0 0; padding-left:20px;'>  Pressure</p></td>\
            <td>Shaolin Dub</td>\
            <td>\
                <div style='width:100%; height:100%;'>\
                    <audio src='./static/hard_music/Shaolin_Dub_-_12_-_Pressure.mp3' style='height:30px; margin-top:5px; padding:0px;' controls>\
                        <h3>遇到不支援的瀏覽器會出現這行字</h3>\
                    </audio>\
                </div>\
            </td>\
        </tr>\
    </table>\
    "
    }
}