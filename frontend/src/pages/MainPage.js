import React from 'react'
import axios from 'axios';
import { Link } from 'react-router-dom'
import ContentLoader from "react-content-loader"

import Parametr from "../components/Parametr";
import DatasetItem from '../components/DatasetItem';

import plus from '../assets/plus.svg';

axios.defaults.xsrfCookieName = 'csrftoken'
axios.defaults.xsrfHeaderName = "X-CSRFTOKEN"

const skeleton = [0, 0, 0, 0, 0];

const dataset = [{
	id: 1
},
{
	id: 2
},
{
	id: 3
},
];

const MyLoader = (props) => (
	<ContentLoader 
	  speed={2}
	  width={"100%"}
	  height={58}
	  backgroundColor="#f7fdfc"
	  foregroundColor="#ebf4ff"
	  {...props}
	>
	  <rect x="0" y="0" rx="10" ry="10" width="100%" height="52"/>
	</ContentLoader>
  )


const MainPage = () => {

	const [datasets, setDatasets] = React.useState(null);
	const [progress, setProgress] = React.useState([]);

	const [generatorParametrs, setGeneratorParametrs] = React.useState(null);
	const [isLoading, setIsLoading] = React.useState(false);
	const [isError, setIsError] = React.useState(false);

	const [selectedParametrs, setSelectedParametrs] = React.useState([]);

	const getProgres = () => {
		axios.get('http://127.0.0.1:8000/api/progress_of_datasets')
		.then(({data}) => {setProgress(data)})
		.catch(e => {console.log(e)});
	}

	const getDatasets = () => {
		axios.get('http://127.0.0.1:8000/api/datasets/')
		.then(({data}) => {setDatasets(data)})
		.catch(e => {console.log(e)});
	}

	const getGeneratorParametrs = () => {
		setIsLoading(true);
		axios.get('http://127.0.0.1:8000/api/add_parameter/')
		.then(({data}) => {setGeneratorParametrs(data); setIsLoading(false);})
		.catch(e => {console.log(e); setIsLoading(false); setIsError(true);});
	}

	const deleteParametr = (id) => {
		axios.delete(`http://127.0.0.1:8000/api/add_parameter/${id}`)
		.then(() => {
			getGeneratorParametrs();
			alert("Параметр генерации успешно удален!");
		})
		.catch(e => console.log(e));
	}
	
	const addDataset = () => {
		if (selectedParametrs.length > 0) {
			console.log(selectedParametrs);
			axios.post(`http://127.0.0.1:8000/api/add_dataset`, selectedParametrs)
			.then(() => {
				alert('Параметры успешно отправлены на генерацию!');
				getDatasets();
				getProgres();
			})
			.catch(e => {console.log(e); alert("Не удалось отправить запрос, попробуйте еще раз")});
		} else {
			alert("Пожалуйста, выберите как минимум 1 параметр генерации");
		}
	} 

	React.useEffect(() => {
		getGeneratorParametrs();
		getDatasets();
		getProgres();
	}, []);

	return (
	<div className="content__wrapper">
			<div className="content__left">
				<h3>Параметры генерации</h3>
				<div className="content pb75">
						{
						!isLoading && (generatorParametrs?.length == 0) && <Link to='/add' className="content__new">Создать параметр генерации<img src={plus}/></Link>
						}
						{
						!isLoading && isError && <div className='content__new error'>Произошла ошибка при загрузке параметров</div>
						}
					<div className="content__scroll">
						{isLoading && skeleton.map((item, i) => {
							return <MyLoader key={i}/>
						})}
						{!isLoading && generatorParametrs && generatorParametrs.map((item, i) => {
							return <Parametr 
								selectedParametrs={selectedParametrs}
								setSelectedParametrs={setSelectedParametrs}
								key={i}
								dataItem={item}
								deleteParametr={() => deleteParametr(item.id)}
							/>
						})}
					</div>
					<div className="content__buttons">
						<Link to='/add' className="content__add-parametr">Добавить параметр</Link>
						<button className="content__generate" onClick={() => addDataset()}>Сгенерировать датасет</button>
					</div>
				</div>
			</div>
			<div className="content__right">
				<div className="content__right-link">
				<h3>Сгенерированный датасет</h3>
				<a href="https://disk.yandex.ru/" target='_blank'>перейти на Яндекс диск</a>
				</div>
				<div className="content">
					<div className="content__scroll">
						{
							datasets && datasets.map((item , i) => {
								// function findObjectById(array, id) {
								// 	for (let i = 0; i < array.length; i++) {
								// 	  if (array[i].id == id) {
								// 		return array[i];
								// 	  }
								// 	}
								// 	return null;
								//   }
								// const currentProgress = findObjectById(progress, item.id);
								const currentProgress = progress[item.id];
								if (item.parameters_of_generation && (item.parameters_of_generation.length > 0)) {
									return <DatasetItem getDatasets={getDatasets} key={i} id={item.id} parameters={item.parameters_of_generation} currentProgress={currentProgress}/>
								} else {
									return null;
								}
							})
						}
					</div>
					{datasets && (datasets.length == 0) && <div className="content__new dataset">Сгенерированный датасет отсутствует</div>} 
				</div>
			</div>
    </div>
  )
}

export default MainPage