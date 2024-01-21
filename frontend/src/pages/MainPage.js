import React from 'react'
import axios from 'axios';
import { Link } from 'react-router-dom'
import ContentLoader from "react-content-loader"

import Parameter from "../components/Parameter";
import DatasetItem from '../components/DatasetItem';

import plus from '../assets/plus.svg';

axios.defaults.xsrfCookieName = 'csrftoken'
axios.defaults.xsrfHeaderName = "X-CSRFTOKEN"

const skeleton = [0, 0, 0, 0, 0];

// const dataset = [{
// 	id: 1
// },
// {
// 	id: 2
// },
// {
// 	id: 3
// },
// ];

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

	const [generatorParameters, setGeneratorParameters] = React.useState(null);
	const [isLoading, setIsLoading] = React.useState(false);
	const [isError, setIsError] = React.useState(false);

	const [selectedParameters, setSelectedParameters] = React.useState([]);

	const [isUpdating, setIsUpdating] = React.useState(false);

	const getProgress = () => {
		axios.get('http://127.0.0.1:8000/api/progress_of_datasets')
		.then(({data}) => {setProgress(data)})
		.catch(e => {console.log(e)});
	}

	
	React.useEffect(() => {
		let interval;
		if (isUpdating) {
			interval = setInterval(() => {
				getProgress();
				getDatasets();
		  	}, 1000);
		} else {
			clearInterval(interval);
			setIsUpdating(false);
		}
		return () => {clearInterval(interval);};
	}, [isUpdating]);
	
	const getDatasets = () => {
		axios.get('http://127.0.0.1:8000/api/datasets/')
		.then(({data}) => {setDatasets(data.reverse())})
		.catch(e => {console.log(e)});
	}

	const getGeneratorParameters = () => {
		setIsLoading(true);
		axios.get('http://127.0.0.1:8000/api/add_parameter/')
		.then(({data}) => {setGeneratorParameters(data.reverse()); setIsLoading(false);})
		.catch(e => {console.log(e); setIsLoading(false); setIsError(true);});
	}

	const deleteParameter = (id) => {
		axios.delete(`http://127.0.0.1:8000/api/add_parameter/${id}`)
		.then(() => {
			getGeneratorParameters();
			alert("Параметр генерации успешно удален!");
		})
		.catch(e => console.log(e));
	}

	const updateData = () => {
		getDatasets();
		getProgress();
	}

	const addDataset = () => {
		if (selectedParameters.length > 0) {
			console.log(selectedParameters);
			axios.post(`http://127.0.0.1:8000/api/add_dataset`, selectedParameters)
			// .then(() => {
			// 	alert('Параметры успешно отправлены на генерацию!');
			// 	getDatasets();
			// 	getProgress();
			// })
			.catch(e => {console.log(e); alert("Не удалось отправить запрос, попробуйте еще раз")});
			// alert('Параметры успешно отправлены на генерацию!');
			setTimeout(updateData, 200);
		} else {
			alert("Пожалуйста, выберите как минимум 1 параметр генерации");
		}
	} 

	React.useEffect(() => {
		getGeneratorParameters();
		getDatasets();
		getProgress();
	}, []);

	return (
	<div className="content__wrapper">
			<div className="content__left">
				<div className="content__right-link">
					<h3>Параметры генерации</h3>
				</div>
				<div className="content pb75">
						{
						!isLoading && (generatorParameters?.length == 0) && <Link to='/add' className="content__new">Создать параметр генерации<img src={plus}/></Link>
						}
						{
						!isLoading && isError && <div className='content__new error'>Произошла ошибка при загрузке параметров</div>
						}
					<div className="content__scroll">
						{isLoading && skeleton.map((item, i) => {
							return <MyLoader key={i}/>
						})}
						{!isLoading && generatorParameters && generatorParameters.map((item, i) => {
							return <Parameter 
								selectedParameters={selectedParameters}
								setSelectedParameters={setSelectedParameters}
								key={i}
								dataItem={item}
								deleteParameter={() => deleteParameter(item.id)}
							/>
						})}
					</div>
					<div className="content__buttons">
						<Link to='/add' className="content__add-parameter">Добавить параметр</Link>
						<button className="content__generate" onClick={() => addDataset()}>Сгенерировать датасет</button>
					</div>
				</div>
			</div>
			<div className="content__right">
				<div className="content__right-link">
				<h3>Сгенерированный датасет</h3>
				<a href="https://vvzunin.me:10003/d/s/tVFkjEa5dJVgkpNCMirx37WFS3vxKPgU/tWINRKjvi7TCinaI8i5arDSuCxhKzd-o-X7RAk_qacAo" target='_blank'>Перейти на Synology Drive</a>
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
									return <DatasetItem 
										getDatasets={getDatasets} 
										ready={item.ready} 
										id={item.id} 
										parameters={item.parameters_of_generation} 
										currentProgress={currentProgress} 
										isUpdating={isUpdating} 
										setIsUpdating={setIsUpdating}
									/>
								} else {
									return null;
								}
							})
						}
					</div>
					{datasets && (datasets.length === 0) && <div className="content__new dataset">Сгенерированный датасет отсутствует</div>} 
				</div>
			</div>
    </div>
  )
}

export default MainPage