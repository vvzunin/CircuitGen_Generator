import React from 'react'
import { Link } from 'react-router-dom'

import Parametr from "../components/Parametr";
import Scheme from "../components/Scheme";

const MainPage = () => {
  return (
    <div className="content__wrapper">
			<div className="content__left">
				<h3>Параметры генерации</h3>
				<div className="content pb75">
					<div className="content__scroll">
						<Parametr/>
						<Parametr/>
					</div>
					<div className="content__buttons">
						<Link to='/add' className="content__add-parametr">Добавить параметр</Link>
						<button className="content__generate">Сгенерировать датасет</button>
					</div>
				</div>
			</div>
			<div className="content__right">
				<h3>Сгенерированный датасет</h3>
				<div className="content">
					<div className="content__scroll">
						<Scheme/>
						<Scheme/>
						<Scheme/>
					</div>
				</div>
			</div>
    </div>
  )
}

export default MainPage