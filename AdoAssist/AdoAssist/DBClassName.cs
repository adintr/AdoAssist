/*----------------------------------------------------------------------------------------------------------------
Version:	AdoAssist 1.20
   Time:	2012-05-22 20:02:51
    SQL:	SELECT * FROM tbl_DEmo
----------------------------------------------------------------------------------------------------------------*/
using System;
using System.Collections.Generic;
using System.Text;

namespace Database
{
	public class DBClassName : Database.IDBOperability
	{
		#region Data and Attr

		/// <summary>
		/// 0 ID adInteger
		/// </summary>
		protected Int32 m_ID;

		/// <summary>
		/// 0 ID adInteger
		/// </summary>
		public Int32 ID
		{
			get
			{
				return m_ID;
			}
			set
			{
				m_ID = value;
			}
		}
	
		/// <summary>
		/// 1 Guid adVarWChar
		/// </summary>
		protected CxString m_strGuid;

		/// <summary>
		/// 1 Guid adVarWChar
		/// </summary>
		public CxString Guid
		{
			get
			{
				return m_strGuid;
			}
			set
			{
				m_strGuid = value;
			}
		}
	
		/// <summary>
		/// 2 Name adVarWChar
		/// </summary>
		protected CxString m_strName;

		/// <summary>
		/// 2 Name adVarWChar
		/// </summary>
		public CxString Name
		{
			get
			{
				return m_strName;
			}
			set
			{
				m_strName = value;
			}
		}
	
		/// <summary>
		/// 3 Age adInteger
		/// </summary>
		protected Int32 m_Age;

		/// <summary>
		/// 3 Age adInteger
		/// </summary>
		public Int32 Age
		{
			get
			{
				return m_Age;
			}
			set
			{
				m_Age = value;
			}
		}
	


		#endregion

		#region IDBOperability

		public void DBSetData(System.Data.DataRow datarow, ulong nFlag)
		{
			var x = datarow;

//			x[0] = ID;
			x[1] = Guid;
			x[2] = Name;
			x[3] = Age;

			/*
//			x["ID"] = ID;
			x["Guid"] = Guid;
			x["Name"] = Name;
			x["Age"] = Age;
			*/

		}

		public void DBGetData(System.Data.IDataReader reader, ulong nFlag)
		{
			var x = reader;

			DBConvert.Convert(out m_ID, x[0]);
			DBConvert.Convert(out m_strGuid, x[1]);
			DBConvert.Convert(out m_strName, x[2]);
			DBConvert.Convert(out m_Age, x[3]);

			/*
			DBConvert.Convert(out m_ID, x["ID"]);
			DBConvert.Convert(out m_strGuid, x["Guid"]);
			DBConvert.Convert(out m_strName, x["Name"]);
			DBConvert.Convert(out m_Age, x["Age"]);
			*/

		}

		#endregion
	}
}
