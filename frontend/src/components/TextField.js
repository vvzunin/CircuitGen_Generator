import { useField } from "formik";

const TextField = ({...props}) => {
  const [field, meta] = useField(props);

  return (
    <label className={(meta.touched && meta.error) ? 'error' : ''}>
      {props.label}
      <input className={(meta.touched && meta.error) ? 'error' : ''} id={props.name} {...field} {...props} />
    </label>
  );
}

export default TextField;